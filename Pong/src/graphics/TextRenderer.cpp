#include "TextRenderer.h"

namespace PongGraphics
{
	TextRenderer::TextRenderer() {}

	TextRenderer::TextRenderer(int height)
		: m_Height(height) {}

	TextRenderer::~TextRenderer()
	{
		m_VAO.CleanBuffers();
	}

	bool TextRenderer::LoadFont(FT_Library& ft, const std::string& filepath)
	{
		FT_Face fontFace;

		// Here we load the font that's provided with the filepath
		if (FT_New_Face(ft, filepath.c_str(), 0, &fontFace))
		{
			std::cout << "(Freetype Error) Failed to load font" << std::endl;
			return false;
		}

		// If we set pixel_width to 0 then the face dynamically calculates the width based on the provided height
		FT_Set_Pixel_Sizes(fontFace, 0, m_Height);

		// Here we set OpenGL's unpack alignment to 1 since we're using one byte per pixel.
		// By default OpenGL requires that texture size is always a multiple of 4 bytes.
		GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

		for (unsigned char c = 0; c < 128; c++)
		{
			// Loading the glyph for a particular character
			if (FT_Load_Char(fontFace, c, FT_LOAD_RENDER))
			{
				std::cout << "(Freetype Error) Failed to load glyph for " << c << std::endl;
				continue;
			}

			// Generating texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				fontFace->glyph->bitmap.width,
				fontFace->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				fontFace->glyph->bitmap.buffer
			);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character ch = {
				texture,
				PongMaths::iVec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows),
				PongMaths::iVec2(fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top),
				fontFace->glyph->advance.x
			};

			m_Characters.insert(std::pair<char, Character>(c, ch));
		}

		FT_Done_Face(fontFace);
		FT_Done_FreeType(ft);

		VertexBuffer* buffer = new VertexBuffer(6 * 4, 4, NULL, GL_DYNAMIC_DRAW);
		m_VAO.GetLayout().Add<float>(GL_FALSE, buffer);
		m_VAO.AddBuffers();

		return true;
	}

	void TextRenderer::Render(Shader& shader, const std::string& text, PongMaths::Vec2 position,
		float scale, PongMaths::Vec3 colour)
	{
		shader.Bind();
		shader.SetUniformVec3f("textColour", colour);

		GLCall(glActiveTexture(GL_TEXTURE0));
		m_VAO.Bind();

		for (auto ch : text)
		{
			Character c = m_Characters[ch];

			// Here we essentially calculate the X and Y positions of the quad and the actual size (width and height).
			// Everything is multiplied by scale so we could easily increase the size of the quad
			float xpos = position.x + c.bearing.x * scale;
			float ypos = position.y - (c.size.y - c.bearing.y) * scale;

			float w = c.size.x * scale;
			float h = c.size.y * scale;

			float vertices[6 * 4] = {
			//	X			Y			tex XY
				xpos,      ypos + h,  0.0f, 0.0f,
				xpos,      ypos,      0.0f, 1.0f,
				xpos + w,  ypos,      1.0f, 1.0f,

				xpos,      ypos + h,  0.0f, 0.0f,
				xpos + w,  ypos,      1.0f, 1.0f,
				xpos + w,  ypos + h,  1.0f, 0.0f
			};

			// Renders glyph texture over the quad and updates the vertex buffer with the new glyph
			glBindTexture(GL_TEXTURE_2D, c.textureID);
			m_VAO.GetLayout().GetElements()[0].buffer->UpdateData(6 * 4 * sizeof(float), vertices);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Advancing for the next glyph is done in 1/64 pixels so we need to bitshift by 6 to get the value in pixels
			position.x += (c.advance >> 6) * scale;
		}


		m_VAO.CleanBuffers();
		m_VAO.Unbind();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

#pragma once

#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "../maths/Vec.h"
#include "Shader.h"
#include "VertexArray.h"

namespace PongGraphics
{
	struct Character
	{
		unsigned int textureID;
		PongMaths::iVec2 size;
		PongMaths::iVec2 bearing;
		unsigned int advance;
	};

	class TextRenderer
	{
	private:
		int m_Height;

		std::map<char, Character> m_Characters;

		VertexArray m_VAO;
	public:
		TextRenderer();
		TextRenderer(int height);
		~TextRenderer();

		/**
		 * \brief Takes a font file and loads the corresponding glyphs, bitmaps and stores them in a Character object
		 * \param ft Reference to an FT_Library object
		 * \param filepath Path to the font being loaded
		 * \return Whether loading was succesfull or not
		 */
		bool LoadFont(FT_Library& ft, const std::string& filepath);

		/**
		 * \brief Calculates each letter position, binds the necessary texture and calls glDrawTriangles to render the text
		 * \param shader Shader to use for rendering the text
		 * \param text Text to be rendered
		 * \param position Position of the text
		 * \param scale Text scale
		 * \param colour Colour of the text
		 */
		void Render(Shader& shader, const std::string& text, PongMaths::Vec2 position, float scale, PongMaths::Vec3 colour);
	};
}
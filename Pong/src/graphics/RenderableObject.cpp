#include "RenderableObject.h"
#include "VertexBufferLayout.h"

namespace PongGraphics
{
	RenderableObject::RenderableObject()
		: m_VAO(nullptr), m_IBO(nullptr), m_Shader(nullptr)
	{
	}

	RenderableObject::RenderableObject(std::string name, PongMaths::Vec3 position, PongMaths::Vec2 size, PongMaths::Vec4 colour, Shader& shader)
		: m_Name(name), m_Position(position), m_Size(size), m_Colour(colour), m_Velocity(0.0f, 0.0f), m_Shader(&shader)
	{
		float vertices[]
		{
			0.0f, 0.0f, position.z,
			0.0f, size.y, position.z,
			size.x, size.y, position.z,
			size.x, 0.0f, 0, position.z
		};

		float colours[]
		{
			colour.x, colour.y , colour.z, colour.w,
			colour.x, colour.y , colour.z, colour.w,
			colour.x, colour.y , colour.z, colour.w,
			colour.x, colour.y , colour.z, colour.w
		};

		unsigned int indices[]
		{
			0, 1, 2,
			2, 3, 0 
		};

		m_VAO = new VertexArray();
		m_IBO = new IndexBuffer(6, indices);

		m_VAO->GetLayout().Add<float>(GL_FALSE, new VertexBuffer(4 * 3, 3, vertices,GL_STATIC_DRAW));
		m_VAO->GetLayout().Add<float>(GL_FALSE, new VertexBuffer(4 * 4, 4, colours, GL_STATIC_DRAW));
		m_VAO->AddBuffers();
	}

	RenderableObject::~RenderableObject()
	{
		delete m_VAO;
		delete m_IBO;
	}
}

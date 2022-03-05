#include "Ball.h"
#include "../graphics/VertexBufferLayout.h"

PongCore::Ball::Ball(const PongMaths::Vec3 position, const PongMaths::Vec4 colour, unsigned int precision, float radius, const PongMaths::Vec2& initVelocity, PongGraphics::Shader& shader)
	: m_Radius(radius)
{
	m_Position = position;
	m_Colour = colour;
	m_Velocity = initVelocity;
	m_Shader = &shader;

	// The vertex count is given by the number of triangles (precision) + 1 (because one extra vertex is needed for the origin
	// point of the circle. Times three for X, Y, Z
	// I also initialized the first vertex to 0.0f to account for the origin point
	float* vertices = new float[(precision + 1) * 3]{0, 0, position.z};

	// Each triangle (precision) has three indices
	unsigned int* indices = new unsigned int[precision * 3];

	float angle = 0.0f;

	for (int i = 0; i < precision; i++)
	{
		vertices[(i + 1) * 3] = radius * cosf(angle);
		vertices[(i + 1) * 3 + 1] = radius * sinf(angle);
		vertices[(i + 1) * 3 + 2] = position.z;

		indices[i * 3] = 0;
		indices[i * 3 + 1] = i + 1;
		indices[i * 3 + 2] = i + 2;

		angle += 2 * PI / float(precision);
	}

	indices[(precision - 1) * 3 + 2] = 1;

	float* colours = new float[(precision + 1) * 4];

	for (int i = 0; i < precision + 1; i++)
	{
		colours[i * 4] = colour.x;
		colours[i * 4 + 1] = colour.y;
		colours[i * 4 + 2] = colour.z;
		colours[i * 4 + 3] = colour.w;
	}

	m_VAO = new PongGraphics::VertexArray();
	m_IBO = new PongGraphics::IndexBuffer(precision * 3, indices);

	m_VAO->GetLayout().Add<float>(GL_FALSE, new PongGraphics::VertexBuffer((precision + 1) * 3, 3, vertices, GL_STATIC_DRAW));
	m_VAO->GetLayout().Add<float>(GL_FALSE, new PongGraphics::VertexBuffer((precision + 1) * 4, 4, colours, GL_STATIC_DRAW));
	m_VAO->AddBuffers();

	delete[] vertices;
	delete[] indices;
}

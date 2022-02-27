#include <cmath>

#include "Ball.h"

PongCore::Ball::Ball(const PongMaths::Vec3 position, unsigned int precision, float radius, PongGraphics::Shader& shader)
	: m_Radius(radius)
{
	m_Position = position;
	m_Shader = &shader;

	// The vertex count is given by the number of triangles (precision) + 1 (because one extra vertex is needed for the origin
	// point of the circle. Times two for both X and Y components.
	// I also initialized the first vertex to 0.0f to account for the origin point
	float* vertices = new float[(precision + 1) * 2]{0, 0};

	// Each triangle (precision) has three indices
	unsigned int* indices = new unsigned int[precision * 3];

	float angle = 0.0f;

	for (int i = 0; i < precision; i++)
	{
		vertices[(i + 1) * 2] = radius * cosf(angle);
		vertices[(i + 1) * 2 + 1] = radius * sinf(angle);

		indices[i * 3] = 0;
		indices[i * 3 + 1] = i + 1;
		indices[i * 3 + 2] = i + 2;

		angle += 2 * PI / float(precision);
	}

	indices[(precision - 1) * 3 + 2] = 1;

	m_VAO = new PongGraphics::VertexArray();
	m_IBO = new PongGraphics::IndexBuffer(precision * 3, indices);

	m_VAO->GetLayout().Add<float>(GL_FALSE, new PongGraphics::VertexBuffer((precision + 1) * 2, 2, vertices));
	m_VAO->AddBuffers();

	delete[] vertices;
	delete[] indices;
}

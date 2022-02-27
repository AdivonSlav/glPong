#include "VertexBufferLayout.h"

namespace PongGraphics
{
	VertexBufferLayout::VertexBufferLayout()
		: m_Stride(0)
	{

	}

	template <typename T>
	void VertexBufferLayout::Add(GLboolean normalized, VertexBuffer* buffer)
	{
		
	}

	template <>
	void VertexBufferLayout::Add<float>(GLboolean normalized, VertexBuffer* buffer)
	{
		m_Elements.push_back(VertexBufferElement{ GL_FLOAT, normalized, buffer });
		m_Stride += sizeof(float) * buffer->GetCount();
	}
}


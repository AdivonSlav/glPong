#include "VertexArray.h"
#include "../utils/GLErrorManager.h"

namespace PongGraphics
{
	VertexArray::VertexArray()
	{
		GLCall(glGenVertexArrays(1, &m_ArrayID));
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_ArrayID));
	}

	void VertexArray::AddBuffers()
	{
		Bind();

		const auto& elements = m_Layout.GetElements();

		for (int i = 0; i < elements.size(); i++)
		{
			elements[i].buffer->Bind();

			GLCall(glEnableVertexAttribArray(i));
			glVertexAttribPointer(i, elements[i].buffer->GetCount(), elements[i].type, GL_FALSE, 0, nullptr);

			elements[i].buffer->Unbind();
		}

		Unbind();
	}

	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(m_ArrayID));
	}

	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}

}

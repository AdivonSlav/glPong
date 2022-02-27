#pragma once

#include <vector>
#include "Buffer.h"
#include "VertexBufferLayout.h"

namespace PongGraphics
{
	class VertexArray
	{
	private:
		unsigned int m_ArrayID;
		VertexBufferLayout m_Layout;
	public:
		VertexArray();
		~VertexArray();

		/**
		 * \brief calls glVertexAttribPointer in order to specify the format and location of the buffered data according to the provided buffer layout
		 * \param vbo Pointer to the VBO
		 * \param layout The layout that will be used to buffer the data
		 */
		void AddBuffers();

		void Bind() const;
		void Unbind() const;

		VertexBufferLayout& GetLayout() { return m_Layout; }
	};
}
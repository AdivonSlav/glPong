#pragma once
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
		 */
		void AddBuffers();

		/**
		 * \brief Invalides the memory of each buffer associated with the vertex array object
		 */
		void CleanBuffers();

		void Bind() const;
		void Unbind() const;

		VertexBufferLayout& GetLayout() { return m_Layout; }
	};
}
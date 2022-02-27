#pragma once

#include <vector>
#include <GL/glew.h>

#include "Buffer.h"
#include "../maths/Vec.h"

namespace PongGraphics
{
	struct VertexBufferElement
	{
		GLuint type;
		GLboolean normalized;
		VertexBuffer* buffer;
	};

	class VertexBufferLayout
	{
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	public:
		VertexBufferLayout();
		~VertexBufferLayout() = default;

		/**
		 * \brief Stores information about the count, data type and stride of the data to be buffered to the VAO
		 * \tparam T The type of data to be added to the buffer layout
		 * \param count Number of components to be added to the buffer layout
		 * \param normalized Whether to normalize or not
		 */
		template<typename T>
		void Add(GLboolean normalized, VertexBuffer* buffer);

		template<>
		void Add<float>(GLboolean normalized, VertexBuffer* buffer);

		std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
		unsigned int GetStride() const { return m_Stride; }
	};
}

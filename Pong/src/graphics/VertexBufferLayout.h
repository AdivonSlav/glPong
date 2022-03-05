
#pragma once

#include <vector>
#include "Buffer.h"

namespace PongGraphics
{
	class VertexBufferLayout
	{
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	public:
		VertexBufferLayout()
			: m_Stride(0)
		{

		}
		~VertexBufferLayout() = default;

		/**
		 * \brief Stores information about the count, data type and stride of the data to be buffered to the VAO
		 * \tparam T The type of data to be added to the buffer layout
		 * \param count Number of components to be added to the buffer layout
		 * \param normalized Whether to normalize or not
		 */
		template<typename T>
		void Add(GLboolean normalized, VertexBuffer* buffer)
		{
			
		}

		/**
		 * \brief Stores information about the count, data type and stride of the data to be buffered to the VAO
		 * \tparam T The type of data to be added to the buffer layout
		 * \param count Number of components to be added to the buffer layout
		 * \param normalized Whether to normalize or not
		 */
		template<>
		void Add<float>(GLboolean normalized, VertexBuffer* buffer)
		{
			m_Elements.push_back(VertexBufferElement{ GL_FLOAT, normalized, buffer });
			m_Stride += sizeof(float) * buffer->GetCount();
		}

		std::vector<VertexBufferElement>& GetElements() { return m_Elements; }
		unsigned int GetStride() const { return m_Stride; }
	};
}

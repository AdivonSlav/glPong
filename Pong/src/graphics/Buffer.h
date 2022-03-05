#pragma once
#include <GL/glew.h>

namespace PongGraphics
{
	class VertexBuffer
	{
	private:
		unsigned int m_BufferID;
		int m_Count;
	public:
		VertexBuffer(unsigned int size, unsigned int count, const void* data, unsigned int usage);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		/**
		 * \brief Updates the vertex buffer with new data
		 * \param size Size in bytes of the new data
		 * \param data Pointer to the new data
		 */
		void UpdateData(unsigned int size, const void* data);

		/**
		 * \brief Calls glInvalidateBufferData and invalidates the content of the buffer
		 */
		void Invalidate();

		inline int GetCount() const { return m_Count; }
	};

	class IndexBuffer
	{
	private:
		unsigned int m_BufferID;
		int m_Count;
	public:
		IndexBuffer(unsigned int count, const void* data);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		/**
		 * \brief Calls glInvalidateBufferData and invalidates the content of the buffer
		 */
		void Invalidate();

		inline int GetCount() const { return m_Count; }
	};

	/**
	 * \brief Struct that contains information about the type of the data in the buffer, whether it's normalized or not and a pointer to the buffer object
	 */
	struct VertexBufferElement
	{
		GLuint type;
		GLboolean normalized;
		VertexBuffer* buffer;
	};

}


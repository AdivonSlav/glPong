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
		VertexBuffer(unsigned int size,unsigned int count, const void* data);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

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

		inline int GetCount() const { return m_Count; }
	};

	struct VertexBufferElement
	{
		GLuint type;
		GLboolean normalized;
		VertexBuffer* buffer;
	};

}


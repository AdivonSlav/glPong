#pragma once

#include <iostream>
#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLog(#x, __FILE__, __LINE__))

inline void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

inline bool GLLog(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "(OpenGL Error) " << error << " - " << function << " " << file << ":" << line << std::endl;
		return false;
	}

	return true;
}

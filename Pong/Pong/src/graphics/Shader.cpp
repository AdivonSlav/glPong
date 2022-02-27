#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Shader.h"

namespace PongGraphics
{
	Shader::Shader()
		: m_ProgramID(0)
	{
		m_ProgramID = CreateShaderProgram();
	}

	Shader::~Shader()
	{
		GLCall(glDeleteProgram(m_ProgramID));
	}

	unsigned int Shader::CompileShader(GLenum type, const std::string& source)
	{
		const char* src = source.c_str();

		unsigned int id = glCreateShader(type);
		GLCall(glShaderSource(id, 1, &src, nullptr));
		GLCall(glCompileShader(id));

		// Simple error logging incase shader compilation fails
		int result;
		GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

		if (result == GL_FALSE)
		{
			int logLength;
			GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength));

			char* errorMessage = new char[logLength];
			glGetShaderInfoLog(id, logLength, &logLength, errorMessage);

			std::cout << "(OpenGL Error) Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
			std::cout << errorMessage << std::endl;

			delete[] errorMessage;
			GLCall(glDeleteShader(id));

			return 0;
		}

		return id;
	}

	unsigned Shader::CreateShaderProgram()
	{
		const std::string vertexSource =
			#include "../shaders/vertex.shader"
		;

		const std::string fragmentSource =
			#include "../shaders/fragment.shader"
		;

		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

		if (vs == 0 || fs == 0)
		{
			std::cout << "(OpenGL Error) Ending shader program creation..." << std::endl;
			return 0;
		}

		GLCall(glAttachShader(program, vs));
		GLCall(glAttachShader(program, fs));
		GLCall(glLinkProgram(program));

		int result;
		GLCall(glGetProgramiv(program, GL_LINK_STATUS, &result));

		if (result == GL_FALSE)
		{
			int logLength;
			GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength));

			char* errorMessage = new char[logLength];
			GLCall(glGetProgramInfoLog(program, logLength, &logLength, errorMessage));

			std::cout << "(OpenGL Error) Failed to link shader program!" << std::endl;
			std::cout << errorMessage << std::endl;

			delete[] errorMessage;
			GLCall(glDeleteProgram(program));

			return 0;
		}

		GLCall(glValidateProgram(program));

		GLCall(glDeleteShader(vs));
		GLCall(glDeleteShader(fs));

		return program;
	}

	void Shader::Bind() const
	{
		GLCall(glUseProgram(m_ProgramID));
	}

	void Shader::Unbind() const
	{
		GLCall(glUseProgram(0));
	}

	int Shader::GetUniformLocation(const char* name) 
	{
		return glGetUniformLocation(m_ProgramID, name);
	}

	void Shader::SetUniformMat4f(const char* name, const PongMaths::Mat4& matrix)
	{
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE , matrix.mat));
	}
}


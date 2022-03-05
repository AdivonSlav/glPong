#pragma once

#include <iostream>
#include "../utils/GLErrorManager.h"
#include "../maths/Maths.h"

namespace PongGraphics
{
	class Shader
	{
	private:
		unsigned int m_ProgramID;

		/**
		 * \brief Takes the source code of the shader and compiles it into a new shader object
		 * \param type Type of shader to be compiled 
		 * \param source The source code of the shader to be compiled
		 * \return An ID to the newly compiled shader object
		 */
		unsigned int CompileShader(GLenum type, const std::string& source);

		/**
		 * \brief Takes the shader objects and attaches them to a program
		 * \return An ID to the newly created shader program
		 */
		unsigned int CreateShaderProgram(const std::string& vs_source, const std::string& fs_source);
	public:
		Shader(const std::string& vs_filepath, const std::string& fs_filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		int GetUniformLocation(const char* name);
		void SetUniformMat4f(const char* name, const PongMaths::Mat4& matrix);
		void SetUniformVec4f(const char* name, PongMaths::Vec4& vec);
		void SetUniformVec3f(const char* name, PongMaths::Vec3& vec);
	};
}



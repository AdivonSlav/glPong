#pragma once

#include <GLFW/glfw3.h>

#include "Shader.h"
#include "../maths/Vec.h"


namespace PongGraphics
{
	class Window
	{
	private:
		GLFWwindow* m_Window;
		std::string m_Title;
		int m_Width;
		int m_Height;
		Shader* m_Shader;

		static bool m_Keys[GLFW_KEY_LAST];

		static bool InitializeGLFW();
		static bool InitializeGLEW();

		/**
		 * \brief Called right after the window object is created. GLFW is also initialized here
		 */
		void CreateWindow();

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void WindowSizeCallback(GLFWwindow* window, int width, int height);
	public:
		__declspec(property(get = GetWidth, put = SetWidth)) int Width;
		__declspec(property(get = GetHeight, put = SetHeight)) int Height;


		Window(const char* title, int width, int height);
		~Window();

		/**
		 * \brief Checks to see whether the window should be closed or not
		 * \return Whether the window is open or not
		 */
		bool IsOpen() const;

		void Clear(const PongMaths::Vec4& clearColor);

		/**
		 * \brief Call this after each frame to swap the buffers and poll for events
		 */
		void Update();

		bool IsKeyPressed(unsigned int key) const;

		inline GLFWwindow*& GetWindow() { return m_Window; }
		inline std::string& GetTitle() { return m_Title; }

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		void SetWidth(int width) { m_Width = width; }
		void SetHeight(int height) { m_Height = height; }
		void SetShader(Shader* shader) { m_Shader = shader; }
	};
}
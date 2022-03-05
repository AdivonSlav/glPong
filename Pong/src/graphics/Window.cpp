#include <GL/glew.h>
#include <iostream>

#include "Window.h"
#include "../utils/GLErrorManager.h"
#include "../maths/Maths.h"

namespace PongGraphics
{
	bool Window::m_Keys[GLFW_KEY_LAST] = { false };

	Window::Window(const char* title, int width, int height)
		: m_Window(nullptr), m_Title(title), m_Width(width), m_Height(height)
	{
		InitializeGLFW();
		CreateWindow();
	}

	Window::~Window()
	{
	    glfwTerminate();
	}


	bool Window::InitializeGLFW()
	{
	    if (!glfwInit())
	    {
	        std::cout << "Error! Could not initialize GLFW!" << std::endl;
	        return false;
	    }

	    return true;
	}

	bool Window::InitializeGLEW()
	{
	    GLenum err = glewInit();

	    if (GLEW_OK != err)
	    {
	        std::cout << "Error! Could not initialize GLEW!" << std::endl;
	        std::cout << glewGetErrorString(err) << std::endl;
	        return false;
	    }

		std::cout << "GLEW " << glewGetString(GLEW_VERSION) << " initialized!" << std::endl;
	    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

		return true;
	}

	void Window::CreateWindow()
	{
	    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);

	    if (!m_Window)
	    {
	        std::cout << "Error! Window could not be created!" << std::endl;
	        glfwTerminate();
	    }

	    glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);
		glfwSetKeyCallback(m_Window, KeyCallback);

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowPos(m_Window, mode->width / 2 - m_Width / 2, mode->height / 2 - m_Height / 2);

	    InitializeGLEW();
	}

	void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* currWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

		currWindow->m_Keys[key] = action != GLFW_RELEASE;
	}

	void Window::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		GLCall(glViewport(0, 0, width, height));
		Window* currWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		currWindow->SetWidth(width);
		currWindow->SetHeight(height);

		PongMaths::Mat4 ortho = PongMaths::Mat4::Orthographic(0.0, width, height, 0.0, -1.0, 1.0);

		currWindow->m_Shader->Bind();
		currWindow->m_Shader->SetUniformMat4f("projMatrix", ortho);
		currWindow->m_Shader->Unbind();
	}

	bool Window::IsOpen() const
	{
	    return !glfwWindowShouldClose(m_Window);
	}

	void Window::Clear(const PongMaths::Vec4& clearColor)
	{
		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::Update()
	{
	    glfwSwapBuffers(m_Window);
	    glfwPollEvents();
	}

	bool Window::IsKeyPressed(unsigned key) const
	{
		if (key >= GLFW_KEY_LAST)
			return false;
		return m_Keys[key];
	}

	bool Window::IsKeyReleased(unsigned key) const
	{
		if (key >= GLFW_KEY_LAST)
			return false;
		return !m_Keys[key];
	}
}


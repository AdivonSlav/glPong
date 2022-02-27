#include <GL/glew.h>

#include "GameLoop.h"

#include "../graphics/Renderer.h"

using namespace PongMaths;

namespace PongCore
{
	constexpr float MOVEMENT_SPEED = 170.0f;
	constexpr float MOVEMENT_OFFSET = 10.0f;

	void Pong::Init()
	{
		window = new PongGraphics::Window("Pong", 960, 540.0f);
		shader = new PongGraphics::Shader();
		window->SetShader(shader);
		paddle1 = new PongGraphics::RenderableObject("Paddle1",Vec3(15, 220, 0), Vec2(20, 100), Vec4(1.0f, 2.0f, 1.0f, 1.0f), *shader);
		paddle2 = new PongGraphics::RenderableObject("Paddle2", Vec3(925, 220, 0), Vec2(20, 100), Vec4(1.0f, 2.0f, 1.0f, 1.0f), *shader);
		ball = new Ball(Vec3(480.0f, 270.0f, 1.0f), 50, 15, *shader);
	}

	void Pong::ProcessInput(double timeDelta)
	{
		if (window->IsKeyPressed(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window->GetWindow(), true);

		if (window->IsKeyPressed(GLFW_KEY_UP) && paddle2->GetPosition().y + paddle2->GetSize().y < window->GetHeight() - MOVEMENT_OFFSET)
			paddle2->TranslateY(MOVEMENT_SPEED * timeDelta);
		else if (window->IsKeyPressed(GLFW_KEY_DOWN) && paddle2->GetPosition().y > 0.0f + MOVEMENT_OFFSET)
			paddle2->TranslateY(-MOVEMENT_SPEED * timeDelta);

		if (window->IsKeyPressed(GLFW_KEY_W) && paddle1->GetPosition().y + paddle1->GetSize().y < window->GetHeight() - MOVEMENT_OFFSET)
			paddle1->TranslateY(MOVEMENT_SPEED * timeDelta);
		else if (window->IsKeyPressed(GLFW_KEY_S) && paddle1->GetPosition().y > 0.0f + MOVEMENT_OFFSET)
			paddle1->TranslateY(-MOVEMENT_SPEED * timeDelta);
	}

	Pong::Pong()
		: window(nullptr), shader(nullptr), paddle1(nullptr), paddle2(nullptr), ball(nullptr)
	{
		Init();
	}

	Pong::~Pong()
	{
		delete paddle1;
		delete paddle2;
		delete ball;
		delete shader;
		delete window;
	}

	void Pong::Run()
	{
		Mat4 ortho = Mat4::Orthographic(0.0f, 960, 540.0f, 0.0f, -1.0f, 1.0f);

		shader->Bind();
		shader->SetUniformMat4f("projMatrix", ortho);

		PongGraphics::Renderer renderer;

		double previousTime = 0.0;

		while (window->IsOpen())
		{
			window->Clear(Vec4(1.0f, 0.5f, 0.5f, 1.0f));

			double currentTime = glfwGetTime();
			double timeDelta = currentTime - previousTime;

			renderer.Queue(*paddle1);
			renderer.Queue(*paddle2);
			renderer.Queue(*ball);
			renderer.Flush();

			ProcessInput(timeDelta);

			previousTime = currentTime;
			window->Update();
		}
	}
}

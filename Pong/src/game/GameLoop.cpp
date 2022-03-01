#include <GL/glew.h>

#include "GameLoop.h"

#include "../graphics/Renderer.h"

using namespace PongMaths;

namespace PongCore
{
	constexpr float MOVEMENT_SPEED = 200.0f;
	constexpr float MOVEMENT_OFFSET = 10.0f;
	const Vec2 INIT_VELOCITY = Vec2(150.0f, 150.0f);

	void Pong::Init()
	{
		window = new PongGraphics::Window("Pong", 960, 540.0f);
		shader = new PongGraphics::Shader();
		window->SetShader(shader);
		paddle1 = new PongGraphics::RenderableObject("Paddle1",Vec3(15, 220, 0), Vec2(20, 100), Vec4(1.0f, 1.0f, 1.0f, 1.0f), *shader);
		paddle2 = new PongGraphics::RenderableObject("Paddle2", Vec3(925, 220, 0), Vec2(20, 100), Vec4(1.0f, 1.0f, 1.0f, 1.0f), *shader);
		ball = new Ball(Vec3(480.0f, 270.0f, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), 50, 10, INIT_VELOCITY, *shader);
	}

	void Pong::ProcessInput(double timeDelta)
	{
		if (window->IsKeyPressed(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window->GetWindow(), true);

		if (window->IsKeyPressed(GLFW_KEY_UP) && paddle2->GetPosition().y + paddle2->GetSize().y < window->GetHeight() - MOVEMENT_OFFSET)
			paddle2->SetVelocity(Vec2(0.0f, MOVEMENT_SPEED));
		else if (window->IsKeyPressed(GLFW_KEY_DOWN) && paddle2->GetPosition().y > 0.0f + MOVEMENT_OFFSET)
			paddle2->SetVelocity(Vec2(0.0f, -MOVEMENT_SPEED));
		else
			paddle2->SetVelocity(Vec2(0.0f, 0.0f));

		if (window->IsKeyPressed(GLFW_KEY_W) && paddle1->GetPosition().y + paddle1->GetSize().y < window->GetHeight() - MOVEMENT_OFFSET)
			paddle1->SetVelocity(Vec2(0.0f, MOVEMENT_SPEED));
		else if (window->IsKeyPressed(GLFW_KEY_S) && paddle1->GetPosition().y > 0.0f + MOVEMENT_OFFSET)
			paddle1->SetVelocity(Vec2(0.0f, -MOVEMENT_SPEED));
		else
			paddle1->SetVelocity(Vec2(0.0f, 0.0f));
	}

	void Pong::UpdatePosition(double timeDelta)
	{
		ball->TranslateX(ball->GetVelocity().x * timeDelta);
		ball->TranslateY(ball->GetVelocity().y * timeDelta);
		paddle1->TranslateY(paddle1->GetVelocity().y * timeDelta);
		paddle2->TranslateY(paddle2->GetVelocity().y * timeDelta);

		// Collision with the top and bottom screen border
		if (ball->GetPosition().y - ball->GetRadius() <= 0 || ball->GetPosition().y + ball->GetRadius() >= window->GetHeight())
		{
			Vec2 newVelocity = ball->GetVelocity();
			newVelocity.Multiply(Vec2(1.0f, -1.0f));
			ball->SetVelocity(newVelocity);
		}
		//

		// Collision with the left and right screen border
		bool toReset = false;

		if (ball->GetPosition().x - ball->GetRadius() <= 0)
		{
			std::cout << "Right player scores!" << std::endl;
			toReset = true;
		}
		else if (ball->GetPosition().x + ball->GetRadius() >= window->GetWidth())
		{
			std::cout << "Left player scores!" << std::endl;
			toReset = true;
		}

		if (toReset)
		{
			Reset();
			toReset = false;
		}
		//

		// Paddle collision
		if (ball->GetPosition().x > window->GetWidth() / 2.0f)
			PaddleCollision(*paddle2, timeDelta);
		else
			PaddleCollision(*paddle1, timeDelta);
		//
	}

	void Pong::PaddleCollision(const PongGraphics::RenderableObject& paddle, double timeDelta)
	{
		Vec3 distance = ball->GetPosition();
		bool paddleCollide = false;

		// Get distance from the center of the ball to the center of the paddle
		distance.Subtract(paddle.GetPosition() + Vec3(paddle.GetSize().x / 2.0f, paddle.GetSize().y / 2.0f,0.0f));
		distance.x = std::abs(distance.x);
		distance.y = std::abs(distance.y);

		// If the distance between the ball and the paddle is shorter or equal to the size of the paddle and the ball radius, then we know a collision has occured
		if (distance.x <= paddle.GetSize().x + ball->GetRadius() && distance.y <= paddle.GetSize().y + ball->GetRadius())
		{
			if (distance.x <= paddle.GetSize().x)
			{
				paddleCollide = true;
				Vec2 newVelocity = ball->GetVelocity();
				newVelocity.Multiply(Vec2(-1.0f, 1.0f));
				ball->SetVelocity(newVelocity);
			}
			else if (distance.y <= paddle.GetSize().y)
			{
				paddleCollide = true;
				Vec2 newVelocity = ball->GetVelocity();
				newVelocity.Multiply(Vec2(1.0f, -1.0f));
				ball->SetVelocity(newVelocity);
			}

			Vec3 squaredDistance = distance - Vec3(paddle.GetSize().x / 2.0f, paddle.GetSize().y / 2.0f, 0.0f);
			squaredDistance.Multiply(squaredDistance);

			if (squaredDistance.x + squaredDistance.y <= std::pow(ball->GetRadius(), 2))
			{
				paddleCollide = true;
				Vec2 newVelocity = ball->GetVelocity();
				newVelocity.Multiply(Vec2(-1.0f, 1.0f));
				ball->SetVelocity(newVelocity);
			}
		}

		if (paddleCollide)
		{
			Vec2 newVelocity = ball->GetVelocity();
			newVelocity.Add(Vec2(0.0f, 0.4f * paddle.GetVelocity().y));
			ball->SetVelocity(newVelocity);

			paddleCollide = false;
		}
	}

	void Pong::Reset()
	{
		ball->SetPosition(Vec3(window->GetWidth() / 2.0f, window->GetHeight() / 2.0f, 1.0f));
		ball->SetVelocity(INIT_VELOCITY);
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
			window->Clear(Vec4(0.0f, 0.0f, 0.0f, 1.0f));

			double currentTime = glfwGetTime();
			double timeDelta = currentTime - previousTime;

			renderer.Queue(*paddle1);
			renderer.Queue(*paddle2);
			renderer.Queue(*ball);
			renderer.Flush();

			ProcessInput(timeDelta);
			UpdatePosition(timeDelta);

			previousTime = currentTime;
			window->Update();
		}
	}
}

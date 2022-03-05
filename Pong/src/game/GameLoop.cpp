#include <GL/glew.h>

#include "GameLoop.h"

#include <string>

#include "../graphics/Renderer.h"
#include "../graphics/TextRenderer.h"

using namespace PongMaths;
using namespace PongCore::PongConst;

namespace PongCore
{
	void Pong::Init()
	{
		window = new PongGraphics::Window("Pong", 960, 540.0f);

		// Probably a better way to do this
		const std::string vs_source = {
			#include "../shaders/vertex.shader"
		};
		const std::string fs_source = {
			#include "../shaders/fragment.shader"
		};
		const std::string text_vertex_source = {
			#include "../shaders/text_vertex.shader"
		};
		const std::string text_fragment_source = {
			#include "../shaders/text_fragment.shader"
		};

		shader = new PongGraphics::Shader(vs_source, fs_source);
		textShader = new PongGraphics::Shader(text_vertex_source, text_fragment_source);
		window->SetShader(shader);
		paddle1 = new PongGraphics::RenderableObject("Paddle1",Vec3(15, 220, 0.0f), Vec2(20, 100), Vec4(1.0f, 1.0f, 1.0f, 1.0f), *shader);
		paddle2 = new PongGraphics::RenderableObject("Paddle2", Vec3(925, 220, 0), Vec2(20, 100), Vec4(1.0f, 1.0f, 1.0f, 1.0f), *shader);
		ball = new Ball(Vec3(480.0f, 270.0f, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), 50, 8, BALL_INIT_VELOCITY, *shader);
		courtLine = new PongGraphics::RenderableObject("Court line", Vec3(window->GetWidth() / 2.0f - 2.5f, 0.0f, 0.0f), Vec2(5.0f, window->GetHeight()), Vec4(0.7f, 0.7f, 0.7f, 1.0f), *shader);
	}

	void Pong::ProcessInput(double timeDelta)
	{
		if (window->IsKeyPressed(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window->GetWindow(), true);
		if (window->IsKeyReleased(GLFW_KEY_SPACE))
			pauseKeyDown = false;
		if (window->IsKeyPressed(GLFW_KEY_SPACE) && !pauseKeyDown)
		{
			isPaused = !isPaused;
			gameSpeed = isPaused ? 0.0f : 1.0f;
			pauseKeyDown = true;
		}

		if (window->IsKeyPressed(GLFW_KEY_UP) && paddle2->GetPosition().y + paddle2->GetSize().y < window->GetHeight() - PADDDLE_OFFSET)
			paddle2->SetVelocity(Vec2(0.0f, PADDLE_SPEED));
		else if (window->IsKeyPressed(GLFW_KEY_DOWN) && paddle2->GetPosition().y > 0.0f + PADDDLE_OFFSET)
			paddle2->SetVelocity(Vec2(0.0f, -PADDLE_SPEED));
		else
			paddle2->SetVelocity(Vec2(0.0f, 0.0f));

		if (window->IsKeyPressed(GLFW_KEY_W) && paddle1->GetPosition().y + paddle1->GetSize().y < window->GetHeight() - PADDDLE_OFFSET)
			paddle1->SetVelocity(Vec2(0.0f, PADDLE_SPEED));
		else if (window->IsKeyPressed(GLFW_KEY_S) && paddle1->GetPosition().y > 0.0f + PADDDLE_OFFSET)
			paddle1->SetVelocity(Vec2(0.0f, -PADDLE_SPEED));
		else
			paddle1->SetVelocity(Vec2(0.0f, 0.0f));
	}

	void Pong::UpdatePosition(double timeDelta)
	{
		ball->TranslateX(ball->GetVelocity().x * timeDelta * gameSpeed);
		ball->TranslateY(ball->GetVelocity().y * timeDelta * gameSpeed);
		paddle1->TranslateY(paddle1->GetVelocity().y * timeDelta * gameSpeed);
		paddle2->TranslateY(paddle2->GetVelocity().y * timeDelta * gameSpeed);

		// Collision with the top and bottom screen border
		if (ball->GetPosition().y - ball->GetRadius() <= 0 || ball->GetPosition().y + ball->GetRadius() >= window->GetHeight())
		{
			Vec2 newVelocity = ball->GetVelocity();
			newVelocity.Multiply(Vec2(1.0f, -1.0f));
			ball->SetVelocity(newVelocity);
		}

		// Collision with the left and right screen border
		char toReset = 0;

		if (ball->GetPosition().x - ball->GetRadius() <= 0)
		{
			rightPlayerScore++;
			toReset = 'R';
			std::cout << leftPlayerScore << " - " << rightPlayerScore << std::endl;
		}
		else if (ball->GetPosition().x + ball->GetRadius() >= window->GetWidth())
		{
			leftPlayerScore++;
			toReset = 'L';
			std::cout << leftPlayerScore << " - " << rightPlayerScore << std::endl;
		}

		if (toReset)
			Reset(toReset);

		// Paddle collision
		if (ball->GetPosition().x > window->GetWidth() / 2.0f)
			PaddleCollision(*paddle2, timeDelta);
		else
			PaddleCollision(*paddle1, timeDelta);
	}

	void Pong::PaddleCollision(const PongGraphics::RenderableObject& paddle, double timeDelta)
	{
		if (frameCollisionCount != -1)
			frameCollisionCount++;

		Vec3 distance = ball->GetPosition();
		bool paddleCollide = false;

		// Get distance from the center of the ball to the center of the paddle
		distance.Subtract(paddle.GetPosition() + Vec3(paddle.GetSize().x / 2.0f, paddle.GetSize().y / 2.0f,0.0f));
		distance.x = std::abs(distance.x);
		distance.y = std::abs(distance.y);

		// Collision only happens if a certain number of frames contained a collision, as defined by the treshold constant
		// If the distance between the ball and the paddle is shorter or equal to the size of the paddle and the ball radius, then we know a collision has occured
		if (frameCollisionCount >= COLLISION_FRAME_TRESHOLD || frameCollisionCount == -1)
		{
			if (distance.x <= paddle.GetSize().x / 2.0f + ball->GetRadius() && distance.y <= paddle.GetSize().y / 2.0f + ball->GetRadius())
			{
				if (distance.x <= paddle.GetSize().x && distance.x <= paddle.GetSize().x + ball->GetRadius())
				{
					paddleCollide = true;
					Vec2 newVelocity = ball->GetVelocity();
					newVelocity.Multiply(Vec2(-1.0f, 1.0f));
					ball->SetVelocity(newVelocity);
				}
				else if (distance.y <= paddle.GetSize().y && distance.y <= paddle.GetSize().y + ball->GetRadius())
				{
					paddleCollide = true;
					Vec2 newVelocity = ball->GetVelocity();
					newVelocity.Multiply(Vec2(1.0f, -1.0f));
					ball->SetVelocity(newVelocity);
				}
			}
		}

		if (paddleCollide)
		{
			// Slight increase in ball velocity after collision
			Vec2 newVelocity = ball->GetVelocity();
			newVelocity.Add(Vec2(0.0f, 0.7f * paddle.GetVelocity().y));
			newVelocity.Multiply(Vec2(1.1f, 1.0f));
			ball->SetVelocity(newVelocity);

			frameCollisionCount = 0;
		}
	}

	void Pong::PrintScore(PongGraphics::TextRenderer& renderer) const
	{
		Vec3 colour = { 1.0f,1.0f,1.0f };
		Vec2 leftScorePosition = { window->GetWidth() / 2.0f - 105.0f, window->GetHeight() - 35.0f };
		Vec2 rightScorePosition = { window->GetWidth() / 2.0f + 85.0f, window->GetHeight() - 35.0f };
		int leftScoreLen = std::to_string(leftPlayerScore).length();

		// Score text position correction, probably a better way to handle this
		if (leftScoreLen != 1)
			leftScorePosition.x -= leftScoreLen * 10.0f;

		textShader->Bind();
		renderer.Render(*textShader, std::to_string(leftPlayerScore), leftScorePosition, 1.0f, colour);
		renderer.Render(*textShader, std::to_string(rightPlayerScore), rightScorePosition, 1.0f, colour);
		textShader->Unbind();
	}

	void Pong::Reset(char& toReset)
	{
		// The starting ball trajectory is reversed towards the player that last scored
		ball->SetPosition(Vec3(window->GetWidth() / 2.0f, window->GetHeight() / 2.0f, 1.0f));
		ball->SetVelocity(toReset=='L'?Vec2()- BALL_INIT_VELOCITY : BALL_INIT_VELOCITY);
		toReset = 0;
		frameCollisionCount = 0;
	}

	Pong::Pong()
		: window(nullptr), shader(nullptr), textShader(nullptr), paddle1(nullptr), paddle2(nullptr), courtLine(nullptr), ball(nullptr), frameCollisionCount(-1), leftPlayerScore(0), rightPlayerScore(0), gameSpeed(1), isPaused(false), pauseKeyDown(false)
	{
		Init();
	}

	Pong::~Pong()
	{
		delete paddle1;
		delete paddle2;
		delete ball;
		delete courtLine;
		delete shader;
		delete textShader;
		delete window;
	}

	void Pong::Run()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Mat4 ortho = Mat4::Orthographic(0.0f, 960, 540.0f, 0.0f, -1.0f, 1.0f);

		shader->Bind();
		shader->SetUniformMat4f("projMatrix", ortho);
		shader->Unbind();
		textShader->Bind();
		textShader->SetUniformMat4f("projMatrix", ortho);
		textShader->Unbind();

		PongGraphics::Renderer renderer;

		FT_Library library;
		PongGraphics::TextRenderer txtRenderer(32);

		if (FT_Init_FreeType(&library))
		{
			std::cout << "(Freetype library) Could not initialize library." << std::endl;
			return;
		}

		txtRenderer.LoadFont(library, "fonts/Fredoka-Regular.ttf");

		double previousTime = 0.0;

		while (window->IsOpen())
		{
			window->Clear(Vec4(0.0f, 0.0f, 0.0f, 1.0f));

			const double currentTime = glfwGetTime();
			const double timeDelta = currentTime - previousTime;

			PrintScore(txtRenderer);

			shader->Bind();
			renderer.Queue(*paddle1);
			renderer.Queue(*paddle2);
			renderer.Queue(*courtLine);
			renderer.Queue(*ball);
			renderer.Flush();
			shader->Unbind();

			ProcessInput(timeDelta);
			UpdatePosition(timeDelta);

			previousTime = currentTime;
			window->Update();
		}
	}
}
 
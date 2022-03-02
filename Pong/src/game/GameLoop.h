#pragma once

#include "Ball.h"
#include "../graphics/Shader.h"
#include "../graphics/Window.h"
#include "../graphics/RenderableObject.h"

namespace PongCore { namespace PongConst {

	constexpr float PADDLE_SPEED = 230.0f;
	constexpr float PADDDLE_OFFSET = 10.0f;
	const PongMaths::Vec2 BALL_INIT_VELOCITY = PongMaths::Vec2(250.0f, 50.0f);

	constexpr int COLLISION_FRAME_TRESHOLD = 10;
}}


namespace PongCore
{
	class Pong
	{
	private:
		PongGraphics::Window* window;
		PongGraphics::Shader* shader;
		PongGraphics::RenderableObject* paddle1;
		PongGraphics::RenderableObject* paddle2;
		Ball* ball;

		int frameCollisionCount;

		void Init();

		void ProcessInput(double timeDelta);
		void UpdatePosition(double timeDelta);
		void PaddleCollision(const PongGraphics::RenderableObject& paddle, double timeDelta);

		void Reset(char& toReset);
	public:
		Pong();
		~Pong();

		void Run();
	};
}
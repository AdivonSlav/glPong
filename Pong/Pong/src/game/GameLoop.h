#pragma once

#include "Ball.h"
#include "../graphics/Shader.h"
#include "../graphics/Window.h"
#include "../graphics/RenderableObject.h"

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

		void Init();

		void ProcessInput(double timeDelta);
	public:
		Pong();
		~Pong();

		void Run();
	};
}
#pragma once

#include "../graphics/RenderableObject.h"

namespace PongCore
{
	class Ball : public PongGraphics::RenderableObject
	{
	private:
		float m_Radius;
	public:
		Ball(const PongMaths::Vec3 position, unsigned int precision, float radius, PongGraphics::Shader& shader);
	};
}
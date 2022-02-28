#pragma once

#include "../graphics/RenderableObject.h"

namespace PongCore
{
	class Ball : public PongGraphics::RenderableObject
	{
	private:
		float m_Radius;
	public:
		Ball(const PongMaths::Vec3 position, const PongMaths::Vec4 colour, unsigned int precision, float radius, const PongMaths::Vec2& initVelocity, PongGraphics::Shader& shader);

		const float GetRadius() const { return m_Radius; }
	};
}
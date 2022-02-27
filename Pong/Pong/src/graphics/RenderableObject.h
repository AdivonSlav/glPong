#pragma once

#include "Buffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "../maths/Maths.h"

namespace PongGraphics
{
	class RenderableObject
	{
	protected:
		std::string m_Name;
		PongMaths::Vec3 m_Position;
		PongMaths::Vec2 m_Size;
		PongMaths::Vec4 m_Colour;

		VertexArray* m_VAO;
		IndexBuffer* m_IBO;
		Shader* m_Shader;
	public:
		RenderableObject();
		RenderableObject(std::string name, PongMaths::Vec3 position, PongMaths::Vec2 size, PongMaths::Vec4 colour, Shader& shader);
		virtual ~RenderableObject();

		inline const PongMaths::Vec3& GetPosition() const { return m_Position; }
		inline const PongMaths::Vec2& GetSize() const { return m_Size; }
		inline const PongMaths::Vec4& GetColour() const { return m_Colour; }

		inline void SetPosition(const PongMaths::Vec3& position) { m_Position = position; }

		inline void TranslateX(float x) { m_Position.x += x; }
		inline void TranslateY(float y) { m_Position.y += y; }

		inline const std::string& GetName() const { return m_Name; }
		inline const VertexArray* GetVAO() const { return m_VAO; }
		inline const IndexBuffer* GetIBO() const { return m_IBO; }
		inline Shader& GetShader() const { return *m_Shader; }
	};
}
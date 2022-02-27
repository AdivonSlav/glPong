#include "Renderer.h"

#include "Window.h"

namespace PongGraphics
{
	void Renderer::Queue(const RenderableObject& renderable)
	{
		m_RenderQueue.push_back(renderable);
	}

	void Renderer::Flush()
	{
		while (!m_RenderQueue.empty())
		{
			const RenderableObject& renderable = m_RenderQueue.front();

			renderable.GetVAO()->Bind();
			renderable.GetIBO()->Bind();

			renderable.GetShader().Bind();

			renderable.GetShader().SetUniformMat4f("modelMatrix", PongMaths::Mat4::Translation(renderable.GetPosition()));

			GLCall(glDrawElements(GL_TRIANGLES, renderable.GetIBO()->GetCount(), GL_UNSIGNED_INT, nullptr));

			renderable.GetVAO()->Unbind();

			m_RenderQueue.pop_front();
		}
	}
}

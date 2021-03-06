#pragma once

#include <deque>
#include "RenderableObject.h"
#include "Window.h"

namespace PongGraphics
{
	class Renderer
	{
	private:
		std::deque<std::reference_wrapper<const RenderableObject>> m_RenderQueue;
		std::deque<std::string> m_TextRenderQueue;
	public:
		/**
		 * \brief Push backs a new renderable object to be deque
		 * \param renderable object to be rendered
		 */
		void Queue(const RenderableObject& renderable);

		/**
		 * \brief Binds all necessary objects, configures the shader and calls glDrawElements
		 */
		void Flush();
	};
}

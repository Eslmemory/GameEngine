#pragma once

#include "GameEngine/Render/GraphicsContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GE {

	class GE_API OpenGLContext : public GraphicsContext{
		
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffer() override;

	public:
		GLFWwindow* m_Window;
	};

}
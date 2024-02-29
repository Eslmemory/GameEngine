#include "gepch.h"
#include "OpenGLContext.h"
#include "GameEngine/Core/Log.h"
#include "GameEngine/Core/Core.h"

namespace GE {

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window) 
	{
		GE_CORE_ASSERT(m_Window, "Window handle is null!")
	}

	void OpenGLContext::Init() {

		glfwMakeContextCurrent(m_Window); 
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GE_ASSERT(status, "Failed to initialize Glad!");

		GE_CORE_INFO("OpenGL Info:");
		GE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		GE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		GE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffer() {
		glfwSwapBuffers(m_Window);
	}

}
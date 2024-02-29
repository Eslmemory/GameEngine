#include "gepch.h"
#include "WindowsWindow.h"
#include "GameEngine/Core/Log.h"
#include "GameEngine/Event/MouseEvent.h"
#include "GameEngine/Event/KeyEvent.h"
#include "GameEngine/Event/ApplicationEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace GE {

	Window* Window::Create(WindowProp& windowProp) {
		return new WindowsWindow(windowProp);
	}

	WindowsWindow::WindowsWindow(WindowProp& windowProp) {
		Init(windowProp);
	}

	WindowsWindow::~WindowsWindow() {
	}

	void WindowsWindow::SetVSync(bool enabled) {
		m_Data.IsVSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.IsVSync;
	}

	void WindowsWindow::Init(const WindowProp& windowProp) {
		m_Data.Width = windowProp.Width;
		m_Data.Height = windowProp.Height;
		m_Data.Title = windowProp.Title;
		
		GE_CORE_INFO("Create Window width {0} height{1}", m_Data.Width, m_Data.Height);
		
		// TODO: Create Window
		int success = glfwInit();
		GE_CORE_ASSERT(success, "GLFW Initialized failed");

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
		GE_CORE_ASSERT(m_Window, "Create window failed");

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			auto event = WindowResizeEvent(width, height);
			data.s_Callback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			auto event = WindowCloseEvent();
			data.s_Callback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS:   
				{
					MouseButtonPressedEvent event(button);
					data.s_Callback(event);
					break;
				}
				case GLFW_RELEASE: 
				{
					MouseButtonReleasedEvent event(button);
					data.s_Callback(event);
					break;
				}
			}
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch(action) {
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0); 
					data.s_Callback(event);
					break;
				}
				case GLFW_RELEASE: 
				{
					KeyReleasedEvent event(key); 
					data.s_Callback(event);
					break;
				}
				case GLFW_REPEAT:  
				{
					KeyPressedEvent event(key, 1); 
					data.s_Callback(event);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			auto event = MouseMovedEvent((int)xpos, (int)ypos);
			data.s_Callback(event);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			auto event = MouseScrollEvent((int)xoffset, (int)yoffset);
			data.s_Callback(event);
		});
	}

	void WindowsWindow::Shutdown() {

	}

	void WindowsWindow::Update() {
		glfwPollEvents();
		m_Context->SwapBuffer();
	}

}
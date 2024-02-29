#include "gepch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"
#include "GameEngine/Core/Log.h"
#include "GameEngine/Event/Event.h"
#include "GameEngine/Render/Renderer.h"

namespace GE {

	Application* Application::s_ApplicationInstance = nullptr;

	Application::Application(std::string& name) {
		GE_ASSERT(!s_ApplicationInstance, "Application Instance has existed");
		s_ApplicationInstance = this;
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProp(name)));
		m_Window->SetCallback(BIND_FUNC(Application, OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application() {

	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(BIND_FUNC(Application, OnWindowResize));
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FUNC(Application, OnWindowClose));

		for (auto& layer = m_LayerStack.rbegin(); layer != m_LayerStack.rend(); layer++) {
			if (e.m_Ishandle)
				break;
			(*layer)->OnEvent(e);
		}
	}

	void Application::run() {

		Renderer::Init();

		while (true) {

			float currentTime = glfwGetTime();
			TimeStep timeStep = currentTime - m_LastTime;
			m_LastTime = currentTime;
			
			for (auto& layer : m_LayerStack) {
				layer->OnUpdate(timeStep);
			}
			
			m_ImGuiLayer->Begin();

			for (auto& layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			m_Window->Update();
		}
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& event) {
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event) {
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());
		return true;
	}

}


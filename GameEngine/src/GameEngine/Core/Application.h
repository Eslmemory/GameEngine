#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "GameEngine/ImGui/ImGuiLayer.h"
#include "GameEngine/Event/ApplicationEvent.h"

namespace GE {

	class GE_API Application
	{
	public:
		Application(std::string& name);
		~Application();

		void OnEvent(Event& e);
		void run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
		 
		inline static Application* Get() { return s_ApplicationInstance; }
		inline Window& GetWindow() { return *m_Window; }
		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		float m_LastTime = 0.0f;

		static Application* s_ApplicationInstance;
	
	};

	Application* CreateApplication();
}

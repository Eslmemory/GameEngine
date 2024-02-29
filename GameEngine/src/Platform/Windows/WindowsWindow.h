#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GameEngine/Core/Window.h"
#include "GameEngine/Render/GraphicsContext.h"

namespace GE{

	class GE_API WindowsWindow : public Window {
	public:
		WindowsWindow(WindowProp& windowProp);
		~WindowsWindow();

		virtual inline uint32_t GetWidth() const override { return m_Data.Width; }
		virtual inline uint32_t GetHeight() const override { return m_Data.Height; }
		virtual void* GetNativeWindow() const override { return m_Window; }
		

		virtual void SetCallback(const EventCallback& callback) override { m_Data.s_Callback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual void Update() override;

		virtual void Init(const WindowProp& windowProp);
		virtual void Shutdown();

	public:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;
		
		
	private:
		EventCallback m_Callback;

		struct WindowData {
			std::string Title;
			uint32_t Width;
			uint32_t Height;
			bool IsVSync;

			EventCallback s_Callback;
		};

		WindowData m_Data;
	};

}


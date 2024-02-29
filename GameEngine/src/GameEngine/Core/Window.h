#pragma once
#include "Core.h"
#include "GameEngine/Event/Event.h"

namespace GE {

	struct GE_API WindowProp {
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		WindowProp(std::string title = "Game Engine", uint32_t width = 1280, uint32_t height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	class GE_API Window {
	public:
		using EventCallback = std::function<void(Event&)>;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void* GetNativeWindow() const = 0;

		virtual void SetCallback(const EventCallback& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void Update() = 0;
		static Window* Create(WindowProp& windowProp);
	private:
		int m_Width, m_Height;
	};

}
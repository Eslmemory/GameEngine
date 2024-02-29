#pragma once

#include "Event.h"

namespace GE {

	class GE_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}
		EVENT_CATEGORY(EventCategoryApplication);
		EVENT_TYPE(WindowClose);
	};

	class GE_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {}

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << "width " << m_Width << ", height " << m_Height;
			return ss.str();
		}

		EVENT_CATEGORY(EventCategoryApplication);
		EVENT_TYPE(WindowResize);

	private:
		int m_Width, m_Height;
	};

	class GE_API ApplicationTick : public Event {
	public:
		ApplicationTick() {};
		EVENT_CATEGORY(EventCategoryApplication);
		EVENT_TYPE(AppTick);
	};

	class GE_API ApplicationUpdate : public Event {
	public:
		ApplicationUpdate() {};
		EVENT_CATEGORY(EventCategoryApplication);
		EVENT_TYPE(AppUpdate);
	};

	class GE_API ApplicationRender : public Event {
	public:
		ApplicationRender() {};
		EVENT_CATEGORY(EventCategoryApplication);
		EVENT_TYPE(AppRender);
	};

}
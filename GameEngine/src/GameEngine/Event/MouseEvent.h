#pragma once

#include "Event.h"

namespace GE {

	class GE_API MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton(int button) const { return m_MouseButton; }
		EVENT_CATEGORY(EventCategoryInput | EventCategoryMouseButton);

	protected:
		MouseButtonEvent(int mouseButton)
			: m_MouseButton(mouseButton) {};

	protected:
		int m_MouseButton;
	};

	class GE_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_MouseButton;
			return ss.str();
		}

		EVENT_TYPE(MouseButtonPressed);
	};

	class GE_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}
		
		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_MouseButton;
			return ss.str();
		}

		EVENT_TYPE(MouseButtonReleased);
	};

	class GE_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(int x, int y)
			: m_X(x), m_Y(y) {}

		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << " x " << m_X << ", y " << m_Y;
			return ss.str();
		} 

		EVENT_CATEGORY(EventCategoryInput | EventCategoryMouse);
		EVENT_TYPE(MouseMoved);

	private:
		int m_X, m_Y;
	};

	class GE_API MouseScrollEvent : public Event {
	public:
		MouseScrollEvent(int xoffset, int yoffset)
			: m_Xoffset(xoffset), m_Yoffset(yoffset) {}

		virtual std::string ToString() {
			std::stringstream ss;
			ss << "MouseScrollEvent: " << " x_offset " << m_Xoffset << ", y_offset " << m_Yoffset;
			return ss.str();
		}

		int GetxOffset() const { return m_Xoffset; }
		int GetYOffset() const { return m_Yoffset; }

		EVENT_CATEGORY(EventCategoryInput | EventCategoryMouse);
		EVENT_TYPE(MouseScrolled);
	private:
		int m_Xoffset, m_Yoffset;
	};

}
#pragma once

#include "Event.h"

namespace GE {

	class GE_API KeyEvent : public Event {
	public:
		inline int GetKeycode() const { return m_Keycode; }
		EVENT_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

	protected:
		KeyEvent(int keycode)
			: m_Keycode(keycode) {}

	protected:
		int m_Keycode;
	};

	class GE_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeatCounts) 
		: KeyEvent(keycode), m_RepeatCounts(repeatCounts) {}
		
		inline int GetRepeatCounts() const { return m_RepeatCounts; }

		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_Keycode << ", repeat: " << m_RepeatCounts;
			return ss.str();
		}

		EVENT_TYPE(KeyPressed);
	private:
		int m_RepeatCounts;
	};

	class GE_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode)
		: KeyEvent(keycode) {}

		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_Keycode;
			return ss.str();
		}

		EVENT_TYPE(KeyReleased);

	};

}
#pragma once

#include "GameEngine/Core/Core.h"
#include <string>
#include <sstream>
#include <functional>

namespace GE {

	enum class EventType {
		None=0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None                       =Bit(0),
		EventCategoryApplication   =Bit(1),
		EventCategoryInput         =Bit(2),
		EventCategoryKeyboard      =Bit(3),
		EventCategoryMouse         =Bit(4),
		EventCategoryMouseButton   =Bit(5)
	};

	#define EVENT_TYPE(x)		static EventType GetEventStaticType() { return EventType::##x;} \
								virtual EventType GetEventType() const { return GetEventStaticType(); } \
								virtual char* GetName() const override { return #x; }

	#define EVENT_CATEGORY(x)   virtual int GetEventCategory() const override { return x; }

	#define BIND_FUNC(Space, x) std::bind(&Space::x, this, std::placeholders::_1)

	class EventDispatcher;

	class GE_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual int GetEventCategory() const = 0;
		virtual char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) { return GetEventCategory() & category; }
	public:
		bool m_Ishandle = false;
	};

	class GE_API EventDispatcher {
	public:
		template <typename T>
		using Eventfn = std::function<bool(T&)>;

		EventDispatcher(Event& event)
			: m_Event(event) {}

		template <typename T>
		bool Dispatch(Eventfn<T> fn) {
			if (T::GetEventStaticType() == m_Event.GetEventType()) {
				m_Event.m_Ishandle = fn(*(T*)(&m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

}

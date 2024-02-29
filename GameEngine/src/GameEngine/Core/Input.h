#pragma once

#include "Core.h"

namespace GE {
	
	class GE_API Input {
	public:
		inline static bool IsMouseButtonPressed(int button) { return s_Input->IsMouseButtonPressedImpl(button); }
		inline static bool IsKeyPressed(int keycode) { return s_Input->IsKeyPressedImpl(keycode); }
		inline static std::pair<float, float> GetMousePosition() { return s_Input->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Input->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Input->GetMouseYImpl(); }

	protected:
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Input;
	};

}
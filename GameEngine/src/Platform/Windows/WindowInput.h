#pragma once

#include "GameEngine/Core/Input.h"

namespace GE{
	
	class GE_API WindowInput : public Input {
	public:
		virtual bool IsMouseButtonPressedImpl(int button);
		virtual bool IsKeyPressedImpl(int keycode);
		virtual std::pair<float, float> GetMousePositionImpl();
		virtual float GetMouseXImpl();
		virtual float GetMouseYImpl();
	};

}


#pragma once
#include "GameEngine/Core/Core.h"

namespace GE {
	
	class GE_API GraphicsContext {

	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
	
	};

}
#pragma once
#include "GameEngine/Core/Core.h"
#include <glm/glm.hpp>

namespace GE {

	class GE_API Camera {

	public:
		virtual glm::mat4 GetViewProjectionMatrix() const = 0;

	};
}


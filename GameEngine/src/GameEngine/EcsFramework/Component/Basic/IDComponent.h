#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/Core/UUID.h"

namespace GE {

	class GE_API IDComponent {
	public:
		IDComponent() = default;
		IDComponent(const IDComponent& idComponent) = default;
		IDComponent(const UUID& id)
			: uuid(id) {}

		~IDComponent() {};

	private:
		UUID uuid;
	};
}
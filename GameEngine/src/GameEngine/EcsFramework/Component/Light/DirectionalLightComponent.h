#pragma once
#include "GameEngine/EcsFramework/Component/ComponentBase.h"

namespace GE {

	class GE_API DirectionalLightComponent : public ComponentBase {
	public:
		DirectionalLightComponent() = default;
		DirectionalLightComponent(const DirectionalLightComponent&) = default;
		DirectionalLightComponent(float intensity)
			: Intensity(intensity) {}


	public:
		float Intensity = 100.0f;
	};
}
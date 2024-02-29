#pragma once
#include "GameEngine/EcsFramework/Component/ComponentBase.h"
#include <glm/glm.hpp>

namespace GE {

	class GE_API PointLightComponent : public ComponentBase {
	public:
		PointLightComponent() = default;
		PointLightComponent(const PointLightComponent&) = default;
		PointLightComponent(float intensity, glm::vec4& lightcolor)
			: Intensity(intensity), LightColor(lightcolor) {}
		
		~PointLightComponent() {}

	public:
		float Intensity = 10.0f;
		glm::vec4 LightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	};
}
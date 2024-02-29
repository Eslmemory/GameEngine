#pragma once
#include "GameEngine/Core/Core.h"

namespace GE {

	class GE_API TagComponent {
	public:
		TagComponent() = default;
		TagComponent(const std::string& tag)
			:Tag(tag) {}
		TagComponent(const TagComponent& tagComponent) = default;
		~TagComponent() {}
	public:
		std::string Tag;
	};
}
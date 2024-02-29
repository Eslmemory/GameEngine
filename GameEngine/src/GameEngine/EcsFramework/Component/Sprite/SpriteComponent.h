#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/Render/Texture.h"
#include <glm/glm.hpp>

namespace GE {

	class GE_API SpriteComponent {
	public:
		SpriteComponent() = default;
		SpriteComponent(const glm::vec4& color)
			: Color(color) {}
		SpriteComponent(const std::shared_ptr<Texture2D> texture)
			: Texture(texture) {}
		SpriteComponent(const SpriteComponent& spriteComponent) = default;
	
	public:
		glm::vec4 Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		std::shared_ptr<Texture2D> Texture;
	};

}
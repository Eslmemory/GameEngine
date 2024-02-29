#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/Camera/Camera.h"
#include "GameEngine/EcsFramework/Component/Sprite/SpriteComponent.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
#include <glm/glm.hpp>

namespace GE {

	class GE_API Render2D {
	public:
		static void Init();
		static void SceneBegin(const Camera& camera);
		static void SceneEnd();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawRotationQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotationQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotationQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotationQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawSprite(const glm::mat4& transform, SpriteComponent& sprite);
	private:
		static void Flush();
		static void StartBatch();
		static void NextBatch();

	public:
		struct Statistics {
			uint32_t DrawCalls = 0;
			uint32_t QuadCounts = 0;

			uint32_t GetVertexCounts() { return QuadCounts * 4; }
			uint32_t GetIndexCounts() { return QuadCounts * 6; }

		};
	};
}
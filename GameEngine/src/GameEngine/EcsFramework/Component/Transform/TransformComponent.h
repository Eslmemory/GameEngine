#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/EcsFramework/Component/ComponentBase.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GE {

	class GE_API TransformComponent : public ComponentBase {
	public:
		TransformComponent() {};
		TransformComponent(const TransformComponent& transforcomponent) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}
		TransformComponent(glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale)
			: Translation(translation), Rotation(rotation), Scale(scale) {}
		~TransformComponent() {};

		glm::mat4 GetTranslationMatrix() const { return glm::translate(glm::mat4(1.0f), Translation); }
		glm::mat4 GetRotationMatrix() const { return  glm::toMat4(glm::quat(Rotation)); }
		glm::mat4 GetScaleMatrix() const { return glm::scale(glm::mat4(1.0f), Scale); }
		
		glm::mat4 GetTransformMatrix() const {
			return glm::translate(glm::mat4(1.0f), Translation) * GetRotationMatrix() * GetScaleMatrix(); 
		}

		void SetTranslation(float x, float y, float z) { Translation = { x, y, z }; }

	public:
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };
	};
}
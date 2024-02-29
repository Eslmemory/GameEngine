#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/Camera/Camera.h"
#include "GameEngine/EcsFramework/Component/Mesh/MeshComponent.h"

#include <glm/glm.hpp>

namespace GE {
	class Render3D {
	public:
		static void Init();
		static void SceneBegin(const Camera& camera);
		static void SceneEnd();

		static void DrawModel(glm::mat4& transform, glm::vec3& cameraPos, MeshComponent& meshComponent, int entityId);
	};
}
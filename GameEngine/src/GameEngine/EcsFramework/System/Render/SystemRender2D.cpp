#include "gepch.h"
#include "GameEngine/Render/Render2D.h"
#include "GameEngine/EcsFramework/Entity/Entity.h"
#include "GameEngine/EcsFramework/Component/Transform/TransformComponent.h"
#include "GameEngine/EcsFramework/Component/Sprite/SpriteComponent.h"
#include "GameEngine/EcsFramework/Component/Camera/CameraComponent.h"
#include "SystemRender2D.h"

namespace GE {
	void SystemRender2D::OnEditorUpdate(EditorCamera& camera) {
		// Camera
		// CameraComponent maincamera;
		// auto cameraView = m_Level->m_Registry.view<CameraComponent>();
		// if (cameraView.size() == 0)
		// 	GE_CORE_ASSERT("There is no primary camera!");
		// for (auto& entity : cameraView) {
		// 	CameraComponent tmp = cameraView.get<CameraComponent>(entity);
		// 	if (tmp.Primary) {
		// 		maincamera = tmp;
		// 		break;
		// 	}
		// }
		
		// Render
		Render2D::SceneBegin(camera);
		// auto transformView = m_Level->m_Registry.view<TransformComponent>();
		// for (auto& entity : transformView) {
		// 	auto& transform = transformView.get<TransformComponent>(entity);
		// 	Render2D::DrawQuad(transform.GetTransformMatrix(), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		// }
		auto group = m_Level->m_Registry.view<TransformComponent, SpriteComponent>();
		for(auto& entity : group) {
			auto& [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
			Render2D::DrawSprite(transform.GetTransformMatrix(), sprite);
		}
		Render2D::SceneEnd();
	}

	void SystemRender2D::OnRuntimeUpdate() {

	}

	void SystemRender2D::OnRuntimeStart() {

	}

	void SystemRender2D::OnRuntimeEnd() {

	}

}
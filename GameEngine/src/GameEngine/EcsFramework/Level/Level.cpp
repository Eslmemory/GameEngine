#include "gepch.h"
#include "GameEngine/EcsFramework/System/Render/SystemRender2D.h"
#include "GameEngine/EcsFramework/System/Render/SystemRender3D.h"
#include "GameEngine/EcsFramework/Component/Transform/TransformComponent.h"
#include "GameEngine/EcsFramework/Component/Camera/CameraComponent.h"
#include "GameEngine/EcsFramework/Component/Basic/IDComponent.h"
#include "GameEngine/EcsFramework/Component/Basic/TagComponent.h"
#include "GameEngine/EcsFramework/Entity/Entity.h"
#include "Level.h"

namespace GE {

	Level::Level() {
		m_System.emplace_back(std::make_shared<SystemRender2D>(this));
		m_System.emplace_back(std::make_shared<SystemRender3D>(this));
	}

	Entity Level::CreateEntity(const std::string& name) {
		return CreateEntityWithUUID(UUID(), name);
	}

	Entity Level::CreateEntityWithUUID(UUID uuid, const std::string& name) {
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<IDComponent>(uuid);
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		return entity;
	}

	void Level::OnRuntimeUpdate() {
		for (auto& system : m_System) {
			system->OnRuntimeUpdate();
		}
	}

	void Level::OnEditorUpdate(EditorCamera& camera) {
		for (auto& system : m_System) {
			system->OnEditorUpdate(camera);
		}
	}

	void Level::OnRuntimeStart() {
		for (auto& system : m_System) {
			system->OnRuntimeStart();
		}
	}

	void Level::OnRuntimeEnd() {
		for (auto& system : m_System) {
			system->OnRuntimeEnd();
		}
	}

	void Level::OnViewportResize(uint32_t width, uint32_t height) {
		auto& view = m_Registry.view<CameraComponent>();
		for (auto& entity : view) {
			CameraComponent& cameraComponent = view.get<CameraComponent>(entity);
			cameraComponent.Camera.SetViewport(width, height);
		}
	}

}
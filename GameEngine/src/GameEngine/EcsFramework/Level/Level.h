#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/EcsFramework/System/System.h"
#include "GameEngine/Camera/EditorCamera.h"
#include "GameEngine/Core/UUID.h"
#include <entt.hpp>

namespace GE {
	
	class System;
	class Entity;
	class GE_API Level {
	public:
		Level();
		~Level() {};

		void OnRuntimeUpdate();
		void OnEditorUpdate(EditorCamera& camera);

		void OnRuntimeStart();
		void OnRuntimeEnd();

		void OnViewportResize(uint32_t width, uint32_t height);

		Entity CreateEntity(const std::string& name);
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());

		template<typename T>
		void OnComponentAdded() {}

	public:
		entt::registry m_Registry;
		std::vector<std::shared_ptr<System>> m_System;
	};
}
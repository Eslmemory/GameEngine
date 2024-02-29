#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/EcsFramework/Level/Level.h"

namespace GE {

	class GE_API Entity {
	public:
		Entity() {};
		Entity(entt::entity entityHandle, Level* level)
			: m_EntityHandle(entityHandle), m_Level(level) {}
		~Entity() {}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			T& component = m_Level->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			return component;
		}

		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args) {
			T& component = m_Level->m_Registry.emplace_or_replace<T>(std::forward<Args>(args)...);
			return component;
		}

		template<typename T>
		T& GetComponent() {
			GE_CORE_ASSERT(false, "Entity does not have component! ");
			T& component = m_Level->m_Registry.get<T>(m_EntityHandle);
			return component;
		}

		template<typename... T>
		std::tuple<T*...> GetComponents() {
			GE_CORE_ASSERT(HasComponent<T>() && ..., "Entity does not have component! ")
			return std::make_tuple<T*...>((&(m_Level->m_Registry.get<T>(m_EntityHandle)))...);
		}

		template<typename... T>
		std::tuple<const T* const...> GetConstComponents() {
			GE_CORE_ASSERT(HasComopnent<T>() && ..., "Entity does not have component! ");
			return std::make_tuple<const T* const...>(((const T* const) & (m_Level->m_Registry.get<T>(m_EntityHandle)))...);
		}
		
		template<typename T>
		bool HasComponent() {
			return m_Level->m_Registry.all_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent() {
			GE_CORE_ASSERT(HasComopnent<T>(), "Entity does not have component! ");
			m_Level->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const {
			return m_EntityHandle != entt::null;
		}

		operator uint32_t() const {
			return (uint32_t)m_EntityHandle;
		}

		bool operator== (const Entity& entity) {
			return (m_EntityHandle == entity.m_EntityHandle) && (m_Level == entity.m_Level);
		}
		
		bool operator!= (const Entity& entity) {
			return !(*this == entity);
		}

	private:
		entt::entity m_EntityHandle{ entt::null };
		Level* m_Level;
	};
}
#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/EcsFramework/Level/Level.h"
#include "GameEngine/Camera/EditorCamera.h"

namespace GE {

	class Level;
	class GE_API System {
	public:
		System() = delete;
		System(Level* level)
			: m_Level(level) {}
		~System() = default;

		virtual void OnEditorUpdate(EditorCamera& camera) {}
		virtual void OnRuntimeUpdate() {}
		virtual void OnRuntimeStart() {}
		virtual void OnRuntimeEnd() {}

	protected:
		Level* m_Level = nullptr;
	};
}

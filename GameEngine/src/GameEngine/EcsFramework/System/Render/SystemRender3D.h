#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/EcsFramework/System/System.h"

namespace GE {

	class GE_API SystemRender3D : public System {
	public:
		SystemRender3D(Level* level)
			: System(level) {}
		~SystemRender3D() {}

		virtual void OnEditorUpdate(EditorCamera& camera) override;
		virtual void OnRuntimeUpdate() override;
		virtual void OnRuntimeStart() override;
		virtual void OnRuntimeEnd() override;
	
	};
}
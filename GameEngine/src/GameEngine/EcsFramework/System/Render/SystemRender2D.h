#pragma once
#include "GameEngine/EcsFramework/System/System.h"

namespace GE {
	class GE_API SystemRender2D : public System {
	public:
		SystemRender2D(Level* level)
			: System(level) {}
		~SystemRender2D() {}

		virtual void OnEditorUpdate(EditorCamera& camera) override;
		virtual void OnRuntimeUpdate() override;
		virtual void OnRuntimeStart() override;
		virtual void OnRuntimeEnd() override;
	};
}

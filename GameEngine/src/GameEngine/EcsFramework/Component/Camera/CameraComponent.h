#pragma once
#include "GameEngine/EcsFramework/Component/ComponentBase.h"
#include "GameEngine/Camera/EditorCamera.h"

namespace GE {
	class GE_API CameraComponent : public ComponentBase {
	public:
		CameraComponent() {};
		~CameraComponent() {};

	public:
		EditorCamera Camera;
		bool Primary;
		bool FixAspectRatio;
	};
}
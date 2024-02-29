#pragma once
#include "GameEngine/EcsFramework/Component/ComponentBase.h"
#include "GameEngine/Mesh/Mesh.h"


namespace GE {

	class MeshComponent : public ComponentBase {
	public:
		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(Mesh& mesh)
			: Mesh(mesh) {}

		~MeshComponent() {}
	public:
		Mesh Mesh;
	};
}
#include "gepch.h"
#include "Render3D.h"
#include "GameEngine/Library/ShaderLibrary.h"

namespace GE {
	void Render3D::Init() {
	
	}

	void Render3D::SceneBegin(const Camera& camera) {
		std::shared_ptr<Shader> shader = Library<Shader>::GetInstance().GetDefaultShader();
		shader->Bind();
		shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Render3D::SceneEnd() {

	}

	void Render3D::DrawModel(glm::mat4& transform, glm::vec3& cameraPos, MeshComponent& meshComponent, int entityId) {
		// TODO:
		std::shared_ptr<Shader> shader = Library<Shader>::GetInstance().GetDefaultShader();
		meshComponent.Mesh.Draw(transform, cameraPos, shader, entityId);
	}
}


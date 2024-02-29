#include "gepch.h"
#include "SystemRender3D.h"
#include "GameEngine/Render/Render3D.h"
#include "GameEngine/EcsFramework/Component/Transform/TransformComponent.h"
#include "GameEngine/EcsFramework/Component/Light/PointLightComponent.h"
#include "GameEngine/Library/ShaderLibrary.h"

#include <entt.hpp>

namespace GE {

	void SystemRender3D::OnEditorUpdate(EditorCamera& camera) {
		Render3D::SceneBegin(camera);
		std::shared_ptr<Shader> defaultShader = Library<Shader>::GetInstance().GetDefaultShader();
		defaultShader->Bind();
		// TODO: light
		int lightCount = 0;
		auto lightGroup = m_Level->m_Registry.view<TransformComponent, PointLightComponent>();
		for (auto& entity : lightGroup) {
			auto& [transform, light] = m_Level->m_Registry.get<TransformComponent, PointLightComponent>(entity);
			glm::vec3 lightPos = transform.Translation;
			float intensity = light.Intensity;
			glm::vec3 lightColor = light.LightColor;

			defaultShader->SetFloat("exposure", 1.0f);
			defaultShader->SetFloat("intensity", intensity);
			defaultShader->SetFloat3("lightPositions[" + std::to_string(lightCount) + "]", lightPos);
			defaultShader->SetFloat3("lightColors[" + std::to_string(lightCount) + "]", lightColor);
			lightCount++;
		}

		defaultShader->SetInt("lightCount", lightCount);

		// Render model
		auto meshGroup = m_Level->m_Registry.view<TransformComponent, MeshComponent>();
		for (auto& entity : meshGroup) {
			auto& [transform, mesh] = m_Level->m_Registry.get<TransformComponent, MeshComponent>(entity);
			Render3D::DrawModel(transform.GetTransformMatrix(), camera.GetCameraPosition(), mesh, (int)entity);
		}

		Render3D::SceneEnd();
	}

	void SystemRender3D::OnRuntimeUpdate() {
		
	}

	void SystemRender3D::OnRuntimeStart() {
	
	}

	void SystemRender3D::OnRuntimeEnd() {
	
	}

}
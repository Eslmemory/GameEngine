#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/Render/Shader.h"
#include "GameEngine/Render/Material.h"
#include "SubMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <optional>

namespace GE {

	class GE_API Mesh {
	public:
		Mesh(const Mesh&) = default;
		Mesh(const std::string& path) {
			// TODO: push default material
			m_Materials.push_back(std::make_shared<Material>());
			LoadModel(path);
		}

		void Draw(glm::mat4& transform, glm::vec3& cameraPos, std::shared_ptr<Shader> shader);
		void Draw(glm::mat4& transform, glm::vec3& cameraPos, std::shared_ptr<Shader> shader, int entityId);

	private:
		void LoadModel(const std::string& path);
		void ProcessNode(const aiScene* scene, aiNode* node, int& subMeshIndex);

		template<typename Vertex>
		SubMesh ProcessMesh(const aiScene* scene, aiMesh* mesh, int& subMeshIndex);

		std::optional<std::vector<MaterialTexture>> LoadMaterialTexture(aiMaterial* material, aiTextureType type, int& subMeshIndex);

	public:
		std::vector<SubMesh> m_SubMeshes;
		std::vector<std::shared_ptr<Material>> m_Materials;

		std::string m_Directory;
	};
}
#include "gepch.h"

#include "Mesh.h"
#include "GameEngine/Core/Log.h"
#include <regex>

namespace GE {
	
	void Mesh::LoadModel(const std::string& path) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
		std::string standardPath = std::regex_replace(path, std::regex("\\\\"), "/");
		m_Directory = standardPath.substr(0, standardPath.find_last_of("/"));

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			GE_CORE_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
			return;
		}

		int subMeshIndex = 0;
		ProcessNode(scene, scene->mRootNode, subMeshIndex);
	}

	void Mesh::ProcessNode(const aiScene* scene, aiNode* node, int& subMeshIndex) {
		for (uint32_t i = 0; i < node->mNumMeshes; i++) {
			uint32_t meshIndex = node->mMeshes[i];
			m_SubMeshes.emplace_back(ProcessMesh<StaticVertex>(scene, scene->mMeshes[meshIndex], subMeshIndex));
			subMeshIndex++;
		}
		for (uint32_t i = 0; i < node->mNumChildren; i++) {
			ProcessNode(scene, node->mChildren[i], subMeshIndex);
		}
	}

	template<typename Vertex>
	SubMesh Mesh::ProcessMesh(const aiScene* scene, aiMesh* mesh, int& subMeshIndex) {

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<MaterialTexture> textures;

		for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			glm::vec3 vec;

			vec.x = 0.5 * mesh->mVertices[i].x;
			vec.y = 0.5 * mesh->mVertices[i].y;
			vec.z = 0.5 * mesh->mVertices[i].z;
			vertex.Position = vec;

			if (mesh->HasNormals()) {
				vec.x = mesh->mNormals[i].x;
				vec.y = mesh->mNormals[i].y;
				vec.z = mesh->mNormals[i].z;

				vertex.Normal = vec;
			}

			if (mesh->HasTangentsAndBitangents()) {
				vec.x = mesh->mTangents[i].x;
				vec.y = mesh->mTangents[i].y;
				vec.z = mesh->mTangents[i].z;
				vertex.Tangent = vec;

				vec.x = mesh->mBitangents[i].x;
				vec.y = mesh->mBitangents[i].y;
				vec.z = mesh->mBitangents[i].z;
				vertex.Bitangent = vec;
			}
			else
			{
				vertex.Tangent = glm::vec3{ 0.0f };
				vertex.Bitangent = glm::vec3{ 0.0f };
			}

			glm::vec2 texcoord = { 0.0f, 0.0f };
			if (mesh->mTextureCoords[0]) {
				texcoord.x = mesh->mTextureCoords[0][i].x;
				texcoord.y = mesh->mTextureCoords[0][i].y;
			}
			vertex.TexCoord = texcoord;

			vertices.push_back(vertex);
		}

		if (mesh->HasFaces()) {
			for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
				aiFace face = mesh->mFaces[i];
				for (uint32_t j = 0; j < face.mNumIndices; j++) {
					indices.push_back(face.mIndices[j]);
				}
			}
		}
		
		m_Materials[subMeshIndex] = std::make_shared<Material>();
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		auto loadTexture = [&](aiTextureType type) {
			auto map = LoadMaterialTexture(material, type, subMeshIndex);
			if(map) textures.insert(textures.end(), map.value().begin(), map.value().end());
		};

		for (uint32_t type = aiTextureType_NONE; type < aiTextureType_AMBIENT_OCCLUSION; type++)
			loadTexture(static_cast<aiTextureType>(type));

		return SubMesh(vertices, indices, textures, subMeshIndex);
	}

	std::optional<std::vector<MaterialTexture>> Mesh::LoadMaterialTexture(aiMaterial* material, aiTextureType type, int& subMeshIndex) {
		uint32_t count = material->GetTextureCount(type);
		std::vector<MaterialTexture> textures;
		for (uint32_t i = 0; i < count; i++) {
			aiString str;
			material->GetTexture(type, i, &str);
			bool skip = false;
			for (unsigned int j = 0; j < m_Materials[subMeshIndex]->m_Textures.size(); j++) {
				if (strcmp(m_Materials[subMeshIndex]->m_Textures[j].path.data(), str.C_Str()) == 0) {
					textures.push_back(m_Materials[subMeshIndex]->m_Textures[j]);
					skip = true;
					break;
				}
			}

			if (!skip) {
				MaterialTexture materialTex;
				std::string filename = (std::string)(str.C_Str());
				filename = m_Directory + "/" + filename;
				materialTex.path = filename;
				try {
					// TODO: remove
					// filename = "D:/VisualStdio/VisualStdio2022/Project/GameEngine/GameEngine/Assets/Models/dancing-stormtrooper/textures/Stormtrooper_D.png";
					materialTex.texture = Texture2D::Create(filename);
				}
				catch (...) {
					GE_CORE_WARN("Load Texture failed!");
					materialTex.texture = Library<Texture2D>::GetInstance().GetDefaultTexture();
					// TODO: load default texture;
				}

				switch (type)
				{
				case aiTextureType_DIFFUSE:
				case aiTextureType_BASE_COLOR:
					materialTex.type = TextureType::Albedo;
					m_Materials[subMeshIndex]->b_UseAlbedoMap = true;
					m_Materials[subMeshIndex]->m_AlbedoMap = materialTex.texture;
					break;
				case aiTextureType_HEIGHT:
					break;
				case aiTextureType_AMBIENT:
				case aiTextureType_AMBIENT_OCCLUSION:
					break;
				case aiTextureType_NORMALS:
				case aiTextureType_NORMAL_CAMERA:
					break;
				case aiTextureType_SPECULAR:
				case aiTextureType_METALNESS:
					break;
				case aiTextureType_DIFFUSE_ROUGHNESS:
					break;
				case aiTextureType_EMISSIVE:
					break;
				}
				textures.push_back(materialTex);
				m_Materials[subMeshIndex]->m_Textures.push_back(materialTex);
			}
		}
		return textures;
	}

	void Mesh::Draw(glm::mat4& transform, glm::vec3& cameraPos, std::shared_ptr<Shader> shader) {
		
		shader->Bind();
		for (size_t i = 0; i < m_SubMeshes.size(); i++) {
			m_SubMeshes[i].Draw();
		}
		shader->UnBind();
	}

	void Mesh::Draw(glm::mat4& transform, glm::vec3& cameraPos, std::shared_ptr<Shader> shader, int entityId) {
		shader->Bind();
		shader->SetMat4("model", transform);
		shader->SetMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(transform))));
		shader->SetFloat3("cameraPos", cameraPos);
		for (size_t i = 0; i < m_SubMeshes.size(); i++) {
			m_SubMeshes[i].Draw(shader, entityId, this);
		}
	}

}
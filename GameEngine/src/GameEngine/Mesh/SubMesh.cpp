#include "gepch.h"
#include "SubMesh.h"
#include "Mesh.h"
#include "GameEngine/Render/RenderCommand.h"
#include <glad/glad.h>

namespace GE {

	SubMesh::SubMesh(const std::vector<StaticVertex>& vertices, const std::vector<uint32_t>& indices)
		: m_StaticVertex(vertices), m_Indices(indices)
	{
		m_VAO = VertexArray::Create();
		m_VBO = VertexBuffer::Create(sizeof(StaticVertex) * vertices.size());
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float3, "a_Normal" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float3, "a_Tangent" },
			{ ShaderDataType::Float3, "a_Bitangent" },
		};
		m_VBO->SetLayout(layout);
		m_VAO->AddVertexBuffer(m_VBO);

		m_IBO = IndexBuffer::Create(indices.size());
		m_VAO->SetIndexBuffer(m_IBO);
	}

	SubMesh::SubMesh(const std::vector<SkinnedVertex>& vertices, const std::vector<uint32_t>& indices) {
		// TODO
	}

	SubMesh::SubMesh(const std::vector<StaticVertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<MaterialTexture>& textures, int materialIndex)
		: m_StaticVertex(vertices), m_Indices(indices), m_Textures(textures), m_MaterialIndex(materialIndex)
	{
		m_VAO = VertexArray::Create();
		m_VBO = VertexBuffer::Create(sizeof(StaticVertex) * vertices.size());
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float3, "a_Normal" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float3, "a_Tangent" },
			{ ShaderDataType::Float3, "a_Bitangent" },
		};
		m_VBO->SetLayout(layout);
		m_VAO->AddVertexBuffer(m_VBO);

		m_IBO = IndexBuffer::Create(indices.size());
		m_VAO->SetIndexBuffer(m_IBO);
	}

	SubMesh::SubMesh(const std::vector<SkinnedVertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<MaterialTexture>& textures, int meshIndex) {
		// TODO
	}

	void SubMesh::Draw() {
		static bool bInit = true;
		if (bInit) {
			bInit = false;
			m_VAO->Bind();
			m_VBO->SetData(m_StaticVertex.data(), sizeof(StaticVertex) * m_StaticVertex.size());			
			m_IBO->SetData(m_Indices.data(), m_Indices.size());
			m_VAO->UnBind();
		}
		RenderCommand::DrawIndexed(m_VAO, m_IBO->GetCount());
	}

	void SubMesh::Draw(const std::shared_ptr<Shader> shader, int entity, Mesh* mesh) {
		if (m_Entity) {
			m_Entity = entity;
			m_VAO->Bind();
			m_VBO->SetData(m_StaticVertex.data(), sizeof(StaticVertex) * m_StaticVertex.size());
			m_IBO->SetData(m_Indices.data(), m_Indices.size());
			m_VAO->UnBind();
		}

		// albedo
		if (mesh->m_Materials[m_MaterialIndex]->b_UseAlbedoMap)
			mesh->m_Materials[m_MaterialIndex]->m_AlbedoMap->Bind(3);
		else
			mesh->m_Materials[m_MaterialIndex]->albedoRGBA->Bind(3);

		// normal
		if (mesh->m_Materials[m_MaterialIndex]->b_UseNormalMap)
			mesh->m_Materials[m_MaterialIndex]->m_NormalMap->Bind(4);
		else
			Library<Texture2D>::GetInstance().GetWhiteTexture()->Bind(4);

		// metaillic
		shader->SetInt("b_UseMetallicMap", mesh->m_Materials[m_MaterialIndex]->b_UseMetallicMap);
		if (mesh->m_Materials[m_MaterialIndex]->b_UseMetallicMap)
			mesh->m_Materials[m_MaterialIndex]->m_MetallicMap->Bind(5);
		else {
			mesh->m_Materials[m_MaterialIndex]->metallicRGBA->Bind(5);
			shader->SetFloat("u_metallic", mesh->m_Materials[m_MaterialIndex]->metallic);
		}

		// roughness
		shader->SetInt("b_UseRoughnessMap", mesh->m_Materials[m_MaterialIndex]->b_UseRoughnessMap);
		if (mesh->m_Materials[m_MaterialIndex]->b_UseRoughnessMap)
			mesh->m_Materials[m_MaterialIndex]->m_RoughnessMap->Bind(5);
		else {
			mesh->m_Materials[m_MaterialIndex]->roughnessRGBA->Bind(5);
			shader->SetFloat("u_roughness", mesh->m_Materials[m_MaterialIndex]->roughness);
		}

		// ao
		if (mesh->m_Materials[m_MaterialIndex]->b_UseAoMap)
			mesh->m_Materials[m_MaterialIndex]->m_AoMap->Bind(5);
		else
			Library<Texture2D>::GetInstance().GetWhiteTexture()->Bind(4);

		shader->SetInt("albedoMap", 3);
		shader->SetInt("normalMap", 4);
		shader->SetInt("metallicMap", 5);
		shader->SetInt("roughnessMap", 6);
		shader->SetInt("aoMap", 7);

		RenderCommand::DrawIndexed(m_VAO, m_IBO->GetCount());
	}

}
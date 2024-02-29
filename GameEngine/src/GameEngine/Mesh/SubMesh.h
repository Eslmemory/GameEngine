#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/Render/VertexArray.h"
#include "GameEngine/Render/Buffer.h"
#include "GameEngine/Render/Material.h"
#include <glm/glm.hpp>

namespace GE {

	struct StaticVertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoord;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
	};

	struct SkinnedVertex {
		// TODO
	};

	class Mesh;
	class GE_API SubMesh {
	public:
		SubMesh(const std::vector<StaticVertex>& vertices, const std::vector<uint32_t>& indices);
		SubMesh(const std::vector<SkinnedVertex>& vertices, const std::vector<uint32_t>& indices);

		SubMesh(const std::vector<StaticVertex>& vertices, const std::vector<uint32_t>& indices, 
			const std::vector<MaterialTexture>& textures, int meshIndex);
		SubMesh(const std::vector<SkinnedVertex>& vertices, const std::vector<uint32_t>& indices, 
			const std::vector<MaterialTexture>& textures, int meshIndex);

		void Draw();
		void Draw(const std::shared_ptr<Shader> shader, int entity, Mesh* mesh);

	public:
		std::vector<StaticVertex> m_StaticVertex;
		std::vector<SkinnedVertex> m_SkinnedVertex;

		uint32_t m_MaterialIndex;
	private:
		std::vector<uint32_t> m_Indices;
		std::vector<MaterialTexture> m_Textures;

		std::shared_ptr<VertexArray> m_VAO;
		std::shared_ptr<VertexBuffer> m_VBO;
		std::shared_ptr<IndexBuffer> m_IBO;

		int m_Entity = -1;
	};
}
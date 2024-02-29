#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/Render/Texture.h"
#include "GameEngine/Render/Shader.h"
#include "GameEngine/Library/TextureLibrary.h"

namespace GE {

	enum struct TextureType {
		Albedo = 0,
		Normal,
		Metalness,
		Roughness,
		AmbientOcclusion,
		Specular,
		Height,
		Emission
	};

	struct MaterialTexture {
		std::shared_ptr<Texture2D> texture;
		TextureType type;
		std::string path;
	};

	class Material {
	public:
		Material() 
		{
			Initialize(); 
		}
		Material(std::shared_ptr<Shader> shader)
			: m_Shader(shader) 
		{
			Initialize();
		}

		void SetShader(std::shared_ptr<Shader> shader) { m_Shader = shader; }
		std::shared_ptr<Shader> GetShader() { return m_Shader; }
	private:
		void Initialize();

	public:
		// albedoMap
		bool b_UseAlbedoMap = false;
		glm::vec4 col = { 1.0f, 1.0f, 1.0f, 1.0f };
		std::shared_ptr<Texture2D> albedoRGBA = Texture2D::Create(1, 1);
		std::shared_ptr<Texture2D> m_AlbedoMap = Library<Texture2D>::GetInstance().GetDefaultTexture();

		// normalMap
		bool b_UseNormalMap = false;
		std::shared_ptr<Texture2D> m_NormalMap = Library<Texture2D>::GetInstance().GetDefaultNormalTexture();

		// metaillicMap
		bool b_UseMetallicMap = false;
		float metallic = 0.1f;
		std::shared_ptr<Texture2D> metallicRGBA = Texture2D::Create(1, 1);
		std::shared_ptr<Texture2D> m_MetallicMap = Library<Texture2D>::GetInstance().Get("DefaultMetallicRoughness");

		// roughnessMap
		bool b_UseRoughnessMap = false;
		float roughness = 0.9f;
		std::shared_ptr<Texture2D> roughnessRGBA = Texture2D::Create(1, 1);
		std::shared_ptr<Texture2D> m_RoughnessMap = Library<Texture2D>::GetInstance().Get("DefaultMetallicRoughness");

		// aoMap
		bool b_UseAoMap = false;
		std::shared_ptr<Texture2D> aoRGBA = Library<Texture2D>::GetInstance().GetWhiteTexture();
		std::shared_ptr<Texture2D> m_AoMap = Library<Texture2D>::GetInstance().GetWhiteTexture();

		std::shared_ptr<Shader> m_Shader;
		std::vector<MaterialTexture> m_Textures;
	};
}
#include "gepch.h"
#include "GameEngine/Manager/ConfigManager.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
#include "TextureLibrary.h"

namespace GE {
	Library<Texture2D>::Library() {
		Add("DefaultTexture", Texture2D::Create(ConfigManager::GetInstance().GetAssetFolder() / "Textures/DefaultTexture.png"));
		Add("DefaultNormal", Texture2D::Create(ConfigManager::GetInstance().GetAssetFolder() / "Textures/DefaultNormal.png"));
		Add("DefaultMetallicRoughness", Texture2D::Create(ConfigManager::GetInstance().GetAssetFolder() / "Textures/black.png"));

		std::shared_ptr<Texture2D> whiteTexture = Texture2D::Create(1, 1);
		uint32_t white = 0xffffffff;
		whiteTexture->SetData(&white, sizeof(uint32_t));
		Add("WhiteTexture", whiteTexture);

		std::shared_ptr<Texture2D> blackTexture = Texture2D::Create(1, 1);
		uint32_t black = 0x00000000;
		whiteTexture->SetData(&black, sizeof(uint32_t));
		Add("BlackTexture", blackTexture);
	}

	std::shared_ptr<Texture2D> Library<Texture2D>::GetWhiteTexture()
	{
		return m_Library["WhiteTexture"];
	}

	std::shared_ptr<Texture2D> Library<Texture2D>::GetBlackTexture()
	{
		return m_Library["BlackTexture"];
	}

	std::shared_ptr<Texture2D> Library<Texture2D>::GetDefaultNormalTexture() {
		return m_Library["DefaultNormal"];
	}

	std::shared_ptr<Texture2D> Library<Texture2D>::GetDefaultTexture() {
		return m_Library["DefaultTexture"];
	}
}
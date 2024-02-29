#include "IconManager.h"

namespace GE {

	std::string ResourcesRoot = "D:/VisualStdio/VisualStdio2022/Project/GameEngine/GameEngine/Resources/";
	std::string AssetsRoot = "D:/VisualStdio/VisualStdio2022/Project/GameEngine/GameEngine/Assets/";
	IconManager::IconManager() {
		Add("MusicIcon", Texture2D::Create(ResourcesRoot + "Icons/music.png"));
		Add("FileIcon", Texture2D::Create(ResourcesRoot + "Icons/ContentBrowser/FileIcon.png"));
		Add("DirectoryIcon", Texture2D::Create(ResourcesRoot + "Icons/ContentBrowser/DirectoryIcon.png"));
		Add("DefaultIcon", Texture2D::Create(AssetsRoot + "Textures/DefaultTexture.png"));
	}
}
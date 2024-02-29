#include "gepch.h"
#include "ConfigManager.h"

namespace GE {

	ConfigManager::ConfigManager() {
		m_RootFolder = "D:/VisualStdio/VisualStdio2022/Project/GameEngine/GameEngine";
		m_AssetFolder = "D:/VisualStdio/VisualStdio2022/Project/GameEngine/GameEngine/Assets";
		m_ResourceFolder = "D:/VisualStdio/VisualStdio2022/Project/GameEngine/GameEngine/Resources";
	}

	const std::filesystem::path& ConfigManager::GetRootFolder() const {
		return m_RootFolder;
	}

	const std::filesystem::path& ConfigManager::GetAssetFolder() const {
		return m_AssetFolder;
	}

	const std::filesystem::path& ConfigManager::GetResourceFolder() const {
		return m_ResourceFolder;
	}

}
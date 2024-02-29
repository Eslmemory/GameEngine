#pragma once

#include "GameEngine/Core/PublicSingleton.h"
#include <filesystem>

namespace GE {

	class GE_API ConfigManager : public Singleton<ConfigManager> {
	public:
		ConfigManager();
		ConfigManager(const ConfigManager&) = delete;
		ConfigManager operator= (const ConfigManager&) = delete;

		const std::filesystem::path& GetRootFolder() const;
		const std::filesystem::path& GetAssetFolder() const;
		const std::filesystem::path& GetResourceFolder() const;

	private:
		std::filesystem::path m_RootFolder;
		std::filesystem::path m_AssetFolder;
		std::filesystem::path m_ResourceFolder;
	};
}
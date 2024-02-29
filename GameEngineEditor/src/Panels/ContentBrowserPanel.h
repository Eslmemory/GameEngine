#pragma once
#include "GameEngine/Core/Core.h"
#include <filesystem>
#include <optional>

namespace GE {
	class GE_API ContentBrowserPanel {
	public:
		ContentBrowserPanel() {};

		void OnImGuiRender(bool* pOpen);

	private:
		void DrawTree();
		void DrawTreeRecursive(const std::filesystem::path& currentPath);
		void DrawContent();

	private:
		// std::filesystem::path m_SelectedDirectory;
		std::filesystem::path m_CurrentDirectory;
		std::optional<std::filesystem::path> m_SelectedDirectory;
	};
}
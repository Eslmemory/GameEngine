#include "gepch.h"
#include "ContentBrowserPanel.h"
#include "Manager/IconManager.h"
#include <imgui/imgui.h>

namespace GE {

	namespace Utils {

		static bool HasDirectoryMember(std::filesystem::path path) {
			for (auto& directory : std::filesystem::directory_iterator(path)) {
				if (directory.is_directory())
					return true;
			}
			return false;
		}

		static bool IsImageFile(std::string& filename) {
			size_t index = filename.find_last_of(".");
			std::string filetype = filename.substr(index + 1);
			if (filetype == "jpg" || filetype == "png" || filetype == "bmp")
				return true;
			else
				return false;
		}

		static bool IsMusicFile(std::string filename) {
			size_t index = filename.find_last_of(".");
			std::string filetype = filename.substr(index + 1);
			if (filetype == "mp3" || filetype == "mp4" || filetype == "wma")
				return true;
			else
				return false;
		}

	}

	void ContentBrowserPanel::OnImGuiRender(bool* pOpen) {

		if (!ImGui::Begin("Browser", pOpen)) {
			ImGui::End();
			return;
		}

		ImGui::Columns(2);
		if (ImGui::BeginChild("CONTENT_BROWSER_TREE")) {
			DrawTree();
			ImGui::EndChild();
		}

		ImGui::NextColumn();
		if (ImGui::BeginChild("CONTENT_BROWSER_CONTENT")) {
			DrawContent();
			ImGui::EndChild();
		}

		ImGui::Columns(1);

		ImGui::End();
	}

	void ContentBrowserPanel::DrawTree() {
		auto path = ConfigManager::GetInstance().GetAssetFolder();
		DrawTreeRecursive(path);
	}

	void ContentBrowserPanel::DrawTreeRecursive(const std::filesystem::path& currentPath) {
		ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick |
			ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_SpanFullWidth;
		ImGuiTreeNodeFlags nodeFlags = baseFlags;

		if (m_SelectedDirectory && *m_SelectedDirectory == currentPath)
		{
			nodeFlags |= ImGuiTreeNodeFlags_Selected;
		}

		bool needOpen = true;
		if (!Utils::HasDirectoryMember(currentPath)) {
			nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
			needOpen = false;
		}

		std::string label = "##" + currentPath.filename().string();
		bool open = ImGui::TreeNodeEx(label.c_str(), nodeFlags);
		if (ImGui::IsItemClicked()) {
			m_SelectedDirectory = currentPath;
		}
		
		std::string& name = currentPath.filename().string();
		ImGui::SameLine();
		ImGui::Text(name.c_str());

		if (open && needOpen) {
			for (const auto& directory : std::filesystem::directory_iterator(currentPath)) {
				auto& path = directory.path();
				if (!std::filesystem::is_directory(path))
					continue;
				DrawTreeRecursive(path);
			}
			ImGui::TreePop();
		}
	}

	void ContentBrowserPanel::DrawContent() {
		if (m_SelectedDirectory) {
			static float thumbnailSize = 128.0f;
			float padding = 8.0f;
			float cellSize = thumbnailSize + padding;
			int columnCount = (int)(ImGui::GetContentRegionAvail().x / cellSize);
			if (columnCount < 1)
				columnCount = 1;

			ImGui::Columns(columnCount, 0, false);

			std::vector<std::filesystem::path> sortedFile;
			int directoryCount = 0;
			for (const auto& file : std::filesystem::directory_iterator(*m_SelectedDirectory)) {
				if (!file.is_directory()) {
					sortedFile.emplace_back(file.path());
				}
				else {
					sortedFile.insert(sortedFile.begin() + directoryCount, file.path());
					directoryCount++;
				}
			}

			for (int i = 0; i < sortedFile.size(); i++) {
				ImGui::BeginGroup();

				std::filesystem::path relativePath = std::filesystem::relative(sortedFile[i], ConfigManager::GetInstance().GetRootFolder());
				std::string filename = relativePath.string();
				std::shared_ptr<Texture2D> icon = i < directoryCount ? IconManager::GetInstance().Get("DirectoryIcon") 
												: IconManager::GetInstance().Get("FileIcon");
				ImGui::PushID(filename.c_str());
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

				if (Utils::IsImageFile(filename)) {
					std::shared_ptr<Texture2D>& image = IconManager::GetInstance().FindOrLoadTexture(sortedFile[i].string());
					ImGui::ImageButton((ImTextureID)image->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1, }, { 1, 0 });
				}
				else if (Utils::IsMusicFile(filename)) {
					ImGui::ImageButton((ImTextureID)IconManager::GetInstance().Get("MusicIcon")->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1, }, { 1, 0 });
				}
				else {
					ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1, }, { 1, 0 });
				}

				if (ImGui::BeginDragDropSource()) {
					const wchar_t* data = sortedFile[i].c_str();
					ImGui::SetDragDropPayload("DND_DEMO_PAYLOAD", (void*)data, (wcslen(data) + 1) * sizeof(wchar_t), ImGuiCond_Once);
					ImGui::EndDragDropSource();
				}

				ImGui::PopStyleColor();

				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
					if(i < directoryCount)
						m_SelectedDirectory = sortedFile[i];
				}

				std::string showName = filename.substr(filename.find_last_of("\\") + 1);
				ImVec2 text_size = ImGui::CalcTextSize(showName.c_str());
				ImVec2 pos = ImGui::GetCursorPos();
				if(text_size.x < thumbnailSize)
					pos.x += (thumbnailSize - text_size.x) * 0.5f + 2.0f;
				ImGui::SetCursorPos(pos);
				ImGui::TextWrapped(showName.c_str());

				ImGui::PopID();
				ImGui::EndGroup();
				ImGui::NextColumn();
			}

			ImGui::Columns(1);
		}
	}

}
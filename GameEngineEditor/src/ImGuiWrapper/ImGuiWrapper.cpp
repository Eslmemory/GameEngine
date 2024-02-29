#include "gepch.h"
#include "ImGuiWrapper.h"

namespace GE::ImGuiWrapper {

	bool TreeExStyle1(const void* id, const std::string& name, ImGuiTreeNodeFlags flags) {
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4.0f, 4.0f });
		ImGui::Separator();
		bool open = ImGui::TreeNodeEx(id, flags, name.c_str());
		ImGui::PopStyleVar();
		return open;
	}

	void ShowTextForward(const std::string& name, float offset) {
		ImGui::Text(name.c_str());
		ImGui::SameLine(offset);
	}

	void ShowSliderWithName(const std::string& name, float* value, float min, float max, float offset) {
		ShowTextForward(name, offset);
		const std::string label = "##" + name;
		ImGui::SliderFloat(label.c_str(), value, min, max, nullptr, ImGuiSliderFlags_NoRoundToFormat);
	}
}
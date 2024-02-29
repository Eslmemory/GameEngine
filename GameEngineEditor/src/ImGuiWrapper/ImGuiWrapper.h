#pragma once
#include <imgui/imgui.h>
#include <string>

namespace GE::ImGuiWrapper {
	bool TreeExStyle1(const void* id, const std::string& name, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Framed 
		| ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding);
	
	void ShowTextForward(const std::string& name, float offset = 130.0f);

	void ShowSliderWithName(const std::string& name, float* value, float min = 0.1f, float max = 10.0f, float offset = 130.0f);
}
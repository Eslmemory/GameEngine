#include "ImGuiWrapper/ImGuiWrapper.h"
#include "Manager/IconManager.h"
#include "SceneHierachyPanel.h"
#include <imgui/imgui.h>
#include <ImGuizmo/ImGuizmo.h>
#include <imgui/imgui_internal.h>
#include <filesystem>

namespace GE {

	static void DrawTwoTexture(const std::string name, bool& flag, std::shared_ptr<Texture2D>& texture1, std::shared_ptr<Texture2D>& texture2) {
		ImGui::Columns(2, nullptr, 0);
		ImGui::SetColumnWidth(0, 250.0f);
		ImGuiWrapper::ShowTextForward(name, 130.0f);
		ImVec2 showImageSize = { 100.0f, 100.0f };
		if (flag) {
			ImGui::ImageButton((ImTextureID)texture1->GetRendererID(), showImageSize, { 0, 1 }, { 1, 0 });
		}
		else {
			ImGui::ImageButton((ImTextureID)texture2->GetRendererID(), showImageSize, { 0, 1 }, { 1, 0 });
		}

		if (ImGui::BeginDragDropTarget()) {
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_PAYLOAD")) {
				const wchar_t* file = (const wchar_t*)payload->Data;
				std::string texFile = std::filesystem::path(file).string();
				texture1 = Texture2D::Create(texFile);
				flag = true;
			}
			ImGui::EndDragDropTarget();
		}

		ImGui::NextColumn();
		ImGui::BeginGroup();
		ImGui::Text("Tiling");
		ImGui::Text("Offset");
		ImGui::SameLine();
		ImGui::EndGroup();
		
		ImGui::Columns(1);
	}

	static void DrawVec3Control(glm::vec3& value, const std::string& name, float resetValue = 0.0f, float columnWidth = 100.0f) {
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];
		
		// ##X是button的唯一表示符，但是多次调用DrawVec3Control会存在冲突，
		// PushID就是在X前面在推入name，组合后形成最终的唯一表示符
		ImGui::PushID(name.c_str());

		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Dummy(ImVec2{ 0.0f, 0.05f });
		ImGui::Text(name.c_str());

		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			value.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &value.x, 0.1f);
		ImGui::PopItemWidth();
		
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			value.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &value.y, 0.1f);
		ImGui::PopItemWidth();

		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			value.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &value.z, 0.1f);
		ImGui::PopItemWidth();
		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
	}
	
	SceneHierachyPanel::SceneHierachyPanel(const std::shared_ptr<Level>& level)
		: m_Level(level) 
	{
	}

	void SceneHierachyPanel::DrawEntity(Entity entity) {
		const char* name = "Unnamed Entity";
		if (entity.HasComponent<TagComponent>())
			name = entity.GetComponent<TagComponent>().Tag.c_str();
		ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		if (ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flag, "")) {
			ImGui::TreePop();
		}
		if (ImGui::IsItemClicked()) {
			m_SelectedEntity = entity;
		}
		ImGui::SameLine();
		ImGui::Text(name);
	}

	void SceneHierachyPanel::DrawComponents(Entity entity) {
		// Tag Component
		if (entity.HasComponent<TagComponent>()) {
			auto& tag = entity.GetComponent<TagComponent>().Tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("##tag", buffer, sizeof(buffer))) {
				tag = std::string(buffer);
			}
		}

		// Add Component Popup
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("Add Component")) {
			ImGui::OpenPopup("AddComponent");
		}

		if (ImGui::BeginPopup("AddComponent")) {
			ImGui::EndPopup();
		}
		ImGui::PopItemWidth();

		// Draw Transform Component
		if (entity.HasComponent<TransformComponent>()) {
			// ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
			auto& component = entity.GetComponent<TransformComponent>();
			DrawUI<TransformComponent>("Transform", entity, [](auto& component) {
				DrawVec3Control(component.Translation, "Translation");
				auto& rotation = glm::degrees(component.Rotation);
				DrawVec3Control(rotation, "Rotation");
				component.Rotation = glm::radians(rotation);
				DrawVec3Control(component.Scale, "Scale", 1.0f);
			});
		}

		// Draw Sprite Component
		if (entity.HasComponent<SpriteComponent>()) {
			auto& component = entity.GetComponent<SpriteComponent>();
			DrawUI<SpriteComponent>("Sprite", entity, [&](auto& component) {
					auto& color = component.Color;
					ImGuiWrapper::ShowTextForward("Color", 130.0f);
				ImGui::ColorEdit4("##Color", &color[0]);

				ImGuiWrapper::ShowTextForward("Texture", 130.0f);
				// ImGui::Button("##Texture", ImVec2{ 100.0f, 100.0f });
				ImGui::PushID(entity.GetComponent<TagComponent>().Tag.c_str());
				if(component.Texture)
					ImGui::ImageButton((ImTextureID)component.Texture->GetRendererID(), 
						ImVec2{ 100.0f, 100.0f }, { 0, 1 }, { 1, 0 });
				else
					ImGui::ImageButton((ImTextureID)(IconManager::GetInstance().Get("DefaultIcon")->GetRendererID()), 
						ImVec2{100.0f, 100.0f}, {0, 1}, {1, 0});
				if (ImGui::BeginDragDropTarget()) {
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_PAYLOAD")) {
						const wchar_t* file = (const wchar_t*)payload->Data;
						std::string texFile = std::filesystem::path(file).string();
						component.Texture = Texture2D::Create(texFile);
					}
					ImGui::EndDragDropTarget();
				}
				ImGui::PopID();
			});
		}

		// Draw Camera Component
		if (entity.HasComponent<CameraComponent>()) {
			auto& component = entity.GetComponent<CameraComponent>();
			DrawUI<CameraComponent>("Camera", entity, [&](auto& component) {
				auto& camera = component.Camera;
				static int itemCurrentIdx = 0;
				const char* ProjectionType[2] = { "Perspective", "Orthographic" };
				ImGuiWrapper::ShowTextForward("Primary", 130.0f);
				ImGui::Checkbox("##Primary", &component.Primary);
				ImGuiWrapper::ShowTextForward("Projection", 130.0f);
				if (ImGui::BeginCombo("##Projection", ProjectionType[itemCurrentIdx])) {
					for (int n = 0; n < 2; n++) {
						const bool isSelected = (itemCurrentIdx == n);
						if (ImGui::Selectable(ProjectionType[n], isSelected))
							itemCurrentIdx = n;
						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				if (ProjectionType[itemCurrentIdx] == "Perspective") {
					ImGuiWrapper::ShowTextForward("Fov", 130.0f);
					float perspectiveFOV = camera.GetFov();
					if (ImGui::DragFloat("##Fov", &perspectiveFOV, 0.1f)) {
						camera.SetFov(perspectiveFOV);
					}

					ImGuiWrapper::ShowTextForward("Near", 130.0f);
					float perspectiveNear = camera.GetNearClip();
					if (ImGui::DragFloat("##Near", &perspectiveNear, 0.1f)) {
						camera.SetNearClip(perspectiveNear);
					}

					ImGuiWrapper::ShowTextForward("Far", 130.0f);
					float perspectiveFar = camera.GetFarClip();
					if (ImGui::DragFloat("##Far", &perspectiveFar, 0.1f)) {
						camera.SetFarClip(perspectiveFar);
					}
				}
				
				// TODO: Orthographic Camera
				if (ProjectionType[itemCurrentIdx] == "Orthographic")
				{
					ImGuiWrapper::ShowTextForward("Size", 130.0f);
					float orthoSize = 10.0f;
					if (ImGui::DragFloat("##Size", &orthoSize)){

					}

					ImGuiWrapper::ShowTextForward("Near", 130.0f);
					float orthoNear = 1.0f;
					if (ImGui::DragFloat("##Near", &orthoNear)) {

					}

					ImGuiWrapper::ShowTextForward("Far", 130.0f);
					float orthoFar = 1000.0f;
					if (ImGui::DragFloat("##Far", &orthoFar)) {

					}

					ImGuiWrapper::ShowTextForward("Fixed Ratio", 130.0f);
					ImGui::Checkbox("##Fixed Aspect Ratio", &component.FixAspectRatio);
				}

			});
		}

		// Draw Light Component
		if (entity.HasComponent<PointLightComponent>()) {
			auto& component = entity.GetComponent<PointLightComponent>();
			DrawUI<PointLightComponent>("Light", entity, [&](auto& component) {
				glm::vec4& color = component.LightColor;
				float& intensity = component.Intensity;
				ImGuiWrapper::ShowTextForward("Color", 130.0f);
				ImGui::ColorEdit4("##LightColor", &color[0]);
				ImGuiWrapper::ShowSliderWithName("LightIntensity", &intensity, 0.0f, 10.0f, 130.0f);
			});
		}

		// Draw Mesh Component
		if (entity.HasComponent<MeshComponent>()) {
			auto& component = entity.GetComponent<MeshComponent>();
			DrawUI<MeshComponent>("Mesh", entity, [&](auto& component) {
				std::shared_ptr<Material>& rootMaterial = component.Mesh.m_Materials[0];
				float& metallic = rootMaterial->metallic;
				float& roughness = rootMaterial->roughness;
				ImGuiWrapper::ShowSliderWithName("Metallic", &metallic, 0.0f, 1.0f, 130.0f);
				ImGuiWrapper::ShowSliderWithName("Roughness", &roughness, 0.0f, 1.0f, 130.0f);
				// ImGuiWrapper::ShowTextForward("Metallic", 130.0f);
				// ImGui::SliderFloat("##Metallic", &intensity, 0.0f, 1.0f, nullptr, ImGuiSliderFlags_NoRoundToFormat);

				ImGui::PushID(std::to_string(uint32_t(entity)).c_str());
				// albedo
				DrawTwoTexture("Albedo", rootMaterial->b_UseAlbedoMap, rootMaterial->m_AlbedoMap, rootMaterial->albedoRGBA);
				// normal
				DrawTwoTexture("Normal", rootMaterial->b_UseNormalMap, rootMaterial->m_NormalMap, Library<Texture2D>::GetInstance().GetDefaultNormalTexture());
				// metaillic
				// DrawTwoTexture("Metaillic", rootMaterial->b_UseMetallicMap, rootMaterial->m_MetallicMap, rootMaterial->metallicRGBA);
				// roughness
				// DrawTwoTexture("Roughness", rootMaterial->b_UseRoughnessMap, rootMaterial->m_RoughnessMap, rootMaterial->roughnessRGBA);
				// ao
				// DrawTwoTexture("AO", rootMaterial->b_UseAoMap, rootMaterial->aoRGBA, rootMaterial->m_AoMap);

				ImGui::PopID();
			});
		}
	}

	void SceneHierachyPanel::OnImGuiRender(bool* p_Open, bool* p_OpenProperties) {
		if (m_Level) {
			ImGui::Begin("Scene Hierarchy", p_Open);
			if (p_Open) {
				m_Level->m_Registry.each([&](entt::entity entityID) {
					Entity entity = { entityID, m_Level.get() };
					DrawEntity(entity);
				});
			}
			ImGui::End();

			ImGui::Begin("Properties", p_OpenProperties);
			if (p_OpenProperties) {
				if (m_SelectedEntity) {
					DrawComponents(m_SelectedEntity);
				}
			}
			ImGui::End();
		}
	}

	template<typename ComponentType, typename UIFunction>
	void SceneHierachyPanel::DrawUI(const std::string& name, Entity& entity, UIFunction uiFunction) {
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed |
			ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		bool open = ImGuiWrapper::TreeExStyle1((void*)typeid(ComponentType).hash_code(), name, treeNodeFlags);
		if (open) {
			uiFunction(entity.GetComponent<ComponentType>());
			ImGui::TreePop();
		}
	}

}
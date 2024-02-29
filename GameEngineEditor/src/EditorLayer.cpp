#include "imgui/imgui.h"
#include "EditorLayer.h"
#include <string>

namespace GE {

	EditorLayer::EditorLayer(const std::string& name)
		: Layer(name)
	{
	}

	void EditorLayer::OnAttach() {
        m_ActiveLevel = std::make_shared<Level>();
        m_SceneHierarchyPanel = std::make_shared<SceneHierachyPanel>(m_ActiveLevel);
        m_ContentBrowserPanel = std::make_shared<ContentBrowserPanel>();
		FramebufferSpecification fbSpec;
		fbSpec.m_Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH24STENCIL8 };
		fbSpec.m_Width = 1280;
		fbSpec.m_Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);

		t_Shader = Shader::Create(ConfigManager::GetInstance().GetAssetFolder() / "Shader/texture.glsl");
		m_EditorCamera = EditorCamera(1280, 720);
        m_EditorCamera.SetCameraFocalPoint(glm::vec3(0.0f, 1.0f, 0.0f));
        m_EditorCamera.SetCameraDistance(2.0f);

		t1_Entity = m_ActiveLevel->CreateEntity("light001");
        t1_Entity.GetComponent<TransformComponent>().SetTranslation(0.0f, 1.0f, 1.0f);
		t1_Entity.AddComponent<PointLightComponent>();
        t1_Entity.AddComponent<CameraComponent>();

		t2_Entity = m_ActiveLevel->CreateEntity("entity002");
		t2_Entity.GetComponent<TransformComponent>().SetTranslation(2.0f, 2.0f, 0.0f);
		glm::vec4 color1 = { 0.0f, 1.0f, 1.0f, 1.0f };
		t2_Entity.AddComponent<SpriteComponent>(color1);
		
		t3_Entity = m_ActiveLevel->CreateEntity("entity003");
		t3_Entity.GetComponent<TransformComponent>().SetTranslation(0.0f, 0.0f, 0.0f);
        Mesh mesh("D:/VisualStdio/VisualStdio2022/Project/GameEngine/GameEngine/Assets/Models/dancing-stormtrooper/source/silly_dancing.fbx");
        t3_Entity.AddComponent<MeshComponent>(mesh);
    }
	
	void EditorLayer::OnDetach() {

	}

	void EditorLayer::OnUpdate(TimeStep time) {

        // Resize 
        if (m_ViewportSize.x >= 0.0f && m_ViewportSize.y >= 0.0f &&
            (m_Framebuffer->GetSpecification().m_Width != m_ViewportSize.x ||
            m_Framebuffer->GetSpecification().m_Height != m_ViewportSize.y)) 
        {
            m_Framebuffer->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_EditorCamera.SetViewport(m_ViewportSize.x, m_ViewportSize.y);
            m_ActiveLevel->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        }

        // Render
		m_Framebuffer->Bind();

        RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        RenderCommand::Clear();

		m_ActiveLevel->OnEditorUpdate(m_EditorCamera);
        m_EditorCamera.OnUpdate();
        // rayTrace.DrawBackground(m_EditorCamera.GetViewProjectionMatrix());
		
        m_Framebuffer->UnBind();
	}

	void EditorLayer::OnEvent(Event& event) {
		m_EditorCamera.OnEvent(event);
	}

	void EditorLayer::OnImGuiRender() {
        // Init Dock
        static bool p_open = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }
        
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;
        
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &p_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();
        
        if (opt_fullscreen)
            ImGui::PopStyleVar(2);
        
        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        // window
        style.WindowMinSize.x = 110.0f;
        style.WindowMinSize.y = 80.0f;
        // slider
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
        style.GrabMinSize = 20.0f;
        style.GrabRounding = 10.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        // Menu
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New")) { GE_INFO("New"); }
                if (ImGui::MenuItem("Open", "Ctrl+O")) { GE_INFO("Open"); }
                if (ImGui::MenuItem("Save", "Ctrl+S")) { GE_INFO("Save"); }
                if (ImGui::MenuItem("Save As..")) { GE_INFO("Save As.."); }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) { GE_INFO("Undo"); }
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) { GE_INFO("Redo"); }
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) { GE_INFO("Cut"); }
                if (ImGui::MenuItem("Copy", "CTRL+C")) { GE_INFO("Copy"); }
                if (ImGui::MenuItem("Paste", "CTRL+V")) { GE_INFO("Paste"); }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // Each Window
        bool p_Open = true;
        bool p_OpenProperties = true;
        bool p_OpenContentBrowser = true;
        
        
        m_ContentBrowserPanel->OnImGuiRender(&p_OpenContentBrowser);
        m_SceneHierarchyPanel->OnImGuiRender(&p_Open, &p_OpenProperties);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Viewport");

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        Application::Get()->GetImGuiLayer()->BlockEvent(!m_ViewportFocused && !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID(0);
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, {0, 1}, {1, 0});
        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::End();
	}

}
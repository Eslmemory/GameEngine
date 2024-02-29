#pragma once
#include "GameEngine.h"
#include "Panels/SceneHierachyPanel.h"
#include "Panels/ContentBrowserPanel.h"

namespace GE {

	class EditorLayer : public Layer {
	public:
		EditorLayer(const std::string& name);
		~EditorLayer() {};

		virtual void OnAttach();
		virtual void OnDetach();

		virtual void OnUpdate(TimeStep time);
		virtual void OnEvent(Event& event);

		virtual void OnImGuiRender();

	private:
		std::shared_ptr<Level> m_ActiveLevel;
		std::shared_ptr<Framebuffer> m_Framebuffer;
		std::shared_ptr<SceneHierachyPanel> m_SceneHierarchyPanel;
		std::shared_ptr<ContentBrowserPanel> m_ContentBrowserPanel;
		EditorCamera m_EditorCamera;

		glm::vec2 m_ViewportSize;

		bool m_ViewportFocused;
		bool m_ViewportHovered;

		// test
		std::shared_ptr<Shader> t_Shader;
		RayTrace rayTrace;

		Entity t1_Entity;
		Entity t2_Entity;
		Entity t3_Entity;
		

		
	};
}
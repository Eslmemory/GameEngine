#pragma once
#include "GameEngine.h"

namespace GE {
	class SceneHierachyPanel {
	public:
		SceneHierachyPanel() = default;
		SceneHierachyPanel(const std::shared_ptr<Level>& level);

		void OnImGuiRender(bool* p_Open, bool* p_OpenProperties);
		void DrawEntity(Entity entity);
		void DrawComponents(Entity entity);

		template<typename ComponentType, typename UIFunction>
		void DrawUI(const std::string& name, Entity& entity, UIFunction uiFunction);

	private:
		std::shared_ptr<Level> m_Level;
		Entity m_SelectedEntity = {};
	};
}
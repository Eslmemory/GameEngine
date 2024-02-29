#pragma once

#include "GameEngine/Core/Layer.h"

namespace GE {

	class GE_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(TimeStep time) override;
		virtual void OnEvent(Event& event) override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		void SetDarkThemeColors();

		void BlockEvent(bool block) { m_BlockEvent = block; }

	private:
		float m_Time = 0.0f;
		bool m_BlockEvent = true;
	};

}



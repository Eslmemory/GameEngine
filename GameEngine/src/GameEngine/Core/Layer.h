#pragma once
#include "GameEngine/Event/Event.h"
#include "GameEngine/Core/TimeStep.h"

namespace GE {

	class GE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer")
			: m_Name(name) {};
		~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate(TimeStep time) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return m_Name; }

	private:
		std::string m_Name;
	};

}


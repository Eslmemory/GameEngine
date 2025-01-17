#include "gepch.h"
#include "LayerStack.h"

namespace GE {

	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() {
		for (auto& it : m_Layers)
			delete it;
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto& it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.insert(m_Layers.begin() + m_LayerInsertIndex, overlay);
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		auto& it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}

}
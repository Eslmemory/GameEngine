#include "gepch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "Render2D.h"

namespace GE {

	void Renderer::Init() {
		RenderCommand::Init();
		Render2D::Init();
	}

	// TODO: render information
	void Renderer::BeingScene() {

	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(std::shared_ptr<VertexArray> vertexArray) {
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::ViewportResize(width, height);
	}
}
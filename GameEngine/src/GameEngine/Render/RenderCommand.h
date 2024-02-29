#pragma once

#include "RenderAPI.h"

namespace GE {

	class GE_API RenderCommand {

	public:
		inline static void Init() { s_RenderAPI->Init(); }
		inline static void SetClearColor(glm::vec4& color) { s_RenderAPI->SetClearColor(color); }
		inline static void Clear() { s_RenderAPI->Clear(); }

		inline static void DrawIndexed(std::shared_ptr<VertexArray> vertexArray) {
			vertexArray->Bind();
			s_RenderAPI->DrawIndexed(vertexArray);
		}

		inline static void DrawIndexed(std::shared_ptr<VertexArray> vertexArray, uint32_t indexCount) {
			vertexArray->Bind();
			s_RenderAPI->DrawIndexed(vertexArray, indexCount);
		}

		inline static void ViewportResize(uint32_t width, uint32_t height) {
			s_RenderAPI->ViewportResize(width, height);
		}

	private:
		static RenderAPI* s_RenderAPI;
	};
}

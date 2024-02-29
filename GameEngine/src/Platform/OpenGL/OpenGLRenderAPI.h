#pragma once
#include "GameEngine/Render/RenderAPI.h"

namespace GE {

	class GE_API OpenGLRenderAPI : public RenderAPI {

	public:
		virtual void Init() override;
		virtual void SetClearColor(glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(std::shared_ptr<VertexArray> vertexArray, uint32_t count = 0) override;

		virtual void ViewportResize(uint32_t width, uint32_t height) override;
	};
}
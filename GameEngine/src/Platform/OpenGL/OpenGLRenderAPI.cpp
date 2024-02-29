#include "gepch.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace GE {

	void OpenGLRenderAPI::Init() {
		// enable blend
		// glEnable(GL_BLEND);
		// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// enable depth
		glEnable(GL_DEPTH_TEST);  // GL_DEPTH
		glDepthFunc(GL_LEQUAL);

		// enable stencil
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glStencilMask(0x00);

		glEnable(GL_LINE_SMOOTH);

		glEnable(GL_MULTISAMPLE);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}

	void OpenGLRenderAPI::SetClearColor(glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLRenderAPI::DrawIndexed(std::shared_ptr<VertexArray> vertexArray, uint32_t count) {
		uint32_t indexCount = count ? count : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderAPI::ViewportResize(uint32_t width, uint32_t height) {
		glViewport(0, 0, width, height);
	}
}
#pragma once
#include "glm/glm.hpp"
#include "GameEngine/Core/Core.h"
#include "GameEngine/Render/VertexArray.h"

namespace GE {

	class GE_API RenderAPI {
	public:
		enum class API {
			None = 0, OpenGL, Vulkan
		};

	public:
		virtual void Init() = 0;

		virtual void SetClearColor(glm::vec4& color) = 0;
		virtual void Clear() = 0;
		
		virtual void DrawIndexed(std::shared_ptr<VertexArray> vertexArray, uint32_t count = 0) = 0;

		virtual void ViewportResize(uint32_t width, uint32_t height) = 0;


		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}
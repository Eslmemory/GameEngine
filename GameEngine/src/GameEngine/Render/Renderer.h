#pragma once
#include "GameEngine/Core/Core.h"
#include "RenderAPI.h"

namespace GE {

	class GE_API Renderer {

	public:
		static void Init();
		static void BeingScene();
		static void EndScene();

		static void Submit(std::shared_ptr<VertexArray> vertexArray);

		static void OnWindowResize(uint32_t width, uint32_t height);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

	};
}
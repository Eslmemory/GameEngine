#include "gepch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GE {

	std::shared_ptr<VertexArray> VertexArray::Create() {
		switch (Renderer::GetAPI()) {
			case RenderAPI::API::None:       GE_ASSERT(false, "RenderAPI::None is currently not supported!");
			case RenderAPI::API::OpenGL:     return std::make_shared<OpenGLVertexArray>();
		}
		GE_ASSERT(false, "Unknown render API!");
		return nullptr;
	}
}
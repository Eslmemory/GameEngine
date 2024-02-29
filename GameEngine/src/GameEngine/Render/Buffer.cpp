#include "gepch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace GE {

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size) {

		switch (Renderer::GetAPI()) {

			case RenderAPI::API::None:   GE_ASSERT(false, "RenderAPI::None is currently not supported!");
			case RenderAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(size);
		}
		GE_CORE_ASSERT(false, "Unknown Render API!");
		return nullptr;

	}

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(void* vertices, uint32_t size) {

		switch (Renderer::GetAPI()) {
		
			case RenderAPI::API::None:   GE_ASSERT(false, "RenderAPI::None is currently not supported!");
			case RenderAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}
		GE_CORE_ASSERT(false, "Unknown Render API!");
		return nullptr;

	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {

		switch (Renderer::GetAPI()) {

			case RenderAPI::API::None:   GE_ASSERT(false, "RenderAPI::None is currently not supported!");
			case RenderAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}
		GE_CORE_ASSERT(false, "Unknown Render API!");
		return nullptr;
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t count) {

		switch (Renderer::GetAPI()) {

		case RenderAPI::API::None:   GE_ASSERT(false, "RenderAPI::None is currently not supported!");
		case RenderAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(count);
		}
		GE_CORE_ASSERT(false, "Unknown Render API!");
		return nullptr;
	}

}
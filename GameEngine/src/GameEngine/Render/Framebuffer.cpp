#include "gepch.h"
#include "Framebuffer.h"
#include "GameEngine/Render/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace GE {

	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec) {
		switch (Renderer::GetAPI()) {
			case RenderAPI::API::None:   GE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			case RenderAPI::API::OpenGL: return std::make_shared<OpenGLFramebuffer>(spec);
		}
		GE_CORE_ASSERT(false, "Unknown Render API!");
		return nullptr;
	}
}
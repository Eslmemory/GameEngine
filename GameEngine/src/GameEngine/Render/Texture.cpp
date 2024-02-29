#include "gepch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace GE {

	std::shared_ptr<Texture2D> Texture2D::Create(const std::filesystem::path& filepath) {
		return Create(filepath.string());
	}

	std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		switch (Renderer::GetAPI()) {
			case RenderAPI::API::None:     GE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			case RenderAPI::API::OpenGL:   return std::make_shared<OpenGLTexture2D>(width, height);
		}
		GE_CORE_ASSERT(false, "Unknown Render API!");
		return nullptr;
	}

	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& filepath) {
		switch (Renderer::GetAPI()) {
			case RenderAPI::API::None:     GE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			case RenderAPI::API::OpenGL:   return std::make_shared<OpenGLTexture2D>(filepath);
		}
		GE_CORE_ASSERT(false, "Unknown Render API!");
		return nullptr;
	}

	std::shared_ptr<CubeMapTexture> CubeMapTexture::Create() {
		switch (Renderer::GetAPI()) {
			case RenderAPI::API::None:     GE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			case RenderAPI::API::OpenGL:   return std::make_shared<OpenGLCubeMapTexture>();
		}
		GE_CORE_ASSERT(false, "Unknown Render API!");
		return nullptr;
	}

	std::shared_ptr<CubeMapTexture> CubeMapTexture::Create(uint32_t width, uint32_t height) {
		switch (Renderer::GetAPI()) {
			case RenderAPI::API::None:     GE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			case RenderAPI::API::OpenGL:   return std::make_shared<OpenGLCubeMapTexture>(width, height);
		}
		GE_CORE_ASSERT(false, "Unknown Render API!");
		return nullptr;
	}

}
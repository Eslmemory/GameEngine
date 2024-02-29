#include "gepch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace GE {

	std::shared_ptr<Shader> Shader::Create(const std::filesystem::path& filepath) {
		return Create(filepath.string());
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vert, const std::string& frag) {

		switch (Renderer::GetAPI()) {
			case RenderAPI::API::None:   GE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			case RenderAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vert, frag);
		}
		GE_CORE_ASSERT(false, "Unknown Render API!");
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& filename) {

		switch (Renderer::GetAPI()) {
			case RenderAPI::API::None:   GE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			case RenderAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filename);
		}
		GE_CORE_ASSERT(false, "Unknown Render API!");
		return nullptr;
	}
}
#pragma once

#include "GameEngine/Render/Shader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace GE {
	
	class OpenGLShader : public Shader {

	public:
		OpenGLShader(const std::string& name, const std::string& vert, const std::string& frag);
		OpenGLShader(const std::string& filename);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual uint32_t GetProgramId() const override;

		virtual void SetInt(const std::string& name, const int value);
		virtual void SetIntArray(const std::string& name, int* value, const uint32_t count);
		virtual void SetFloat3Array(const std::string& name, float* value, const uint32_t count);
		virtual void SetFloat(const std::string& name, const float value);
		virtual void SetFloat2(const std::string& name, const glm::vec2& value);
		virtual void SetFloat3(const std::string& name, const glm::vec3& value);
		virtual void SetFloat4(const std::string& name, const glm::vec4& value);
		virtual void SetMat3(const std::string& name, const glm::mat3& value);
		virtual void SetMat4(const std::string& name, const glm::mat4& value);

		std::string ReadFile(const std::string& filename);
		std::unordered_map<GLenum, std::string> PreProcess(std::string& content);
		void CompileShader(std::unordered_map<GLenum, std::string>& shaderSource);

	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}
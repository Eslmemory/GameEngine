#pragma once
#include "GameEngine/Core/Core.h"
#include <glm/glm.hpp>

namespace GE {

	class GE_API Shader {

	public:
		virtual ~Shader() = default;
		
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual uint32_t GetProgramId() const = 0;

		virtual void SetInt(const std::string& name, const int value) = 0;
		virtual void SetIntArray(const std::string& name, int* value, const uint32_t count) = 0;
		virtual void SetFloat3Array(const std::string& name, float* value, const uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, const float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vert, const std::string& frag);
		static std::shared_ptr<Shader> Create(const std::string& filename);
		static std::shared_ptr<Shader> Create(const std::filesystem::path& filepath);
	};
}
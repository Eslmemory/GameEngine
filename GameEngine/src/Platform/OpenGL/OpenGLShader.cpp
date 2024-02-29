#include "gepch.h"
#include "GameEngine/Core/Log.h"
#include "OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

namespace GE {

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment")
			return GL_FRAGMENT_SHADER;
		GE_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vert, const std::string& frag)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> shaderSource;
		shaderSource[GL_VERTEX_SHADER] = vert;
		shaderSource[GL_FRAGMENT_SHADER] = frag;
		CompileShader(shaderSource);
	}

	OpenGLShader::OpenGLShader(const std::string& filename) 
	{
		std::string content = ReadFile(filename);
		std::unordered_map<GLenum, std::string> result = PreProcess(content);
		CompileShader(result);

		// /test.glsl
		size_t pos = filename.find_last_of("/") + 1;
		size_t dot = filename.rfind(".");
		dot = (dot == std::string::npos) ? filename.size() : dot;
		m_Name = filename.substr(pos, dot - pos);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::CompileShader(std::unordered_map<GLenum, std::string>& shaderSource) {
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)shaderSource[GL_VERTEX_SHADER].c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			GE_CORE_ERROR("{0}", infoLog.data());
			GE_CORE_ASSERT(false, "Shader compilation failure!");

			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)shaderSource[GL_FRAGMENT_SHADER].c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			GE_CORE_ERROR("{0}", infoLog.data());
			GE_CORE_ASSERT(false, "Shader link failure!");

			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	std::string OpenGLShader::ReadFile(const std::string& filename) {
		std::string result;
		std::ifstream infile(filename, std::ios::in, std::ios::binary);
		if (infile) {
			infile.seekg(0, infile.end);
			result.resize(infile.tellg());
			infile.seekg(0, infile.beg);
			infile.read(&result[0], result.size());
		}
		else {
			GE_CORE_ASSERT(false, filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(std::string& content) {
		std::unordered_map<GLenum, std::string> result;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = content.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = content.find_first_of("\r\n", pos);
			GE_CORE_ASSERT(col != std::string::npos, "Syntax error! ");
			size_t tmp = pos + typeTokenLength + 1;
			std::string type = content.substr(tmp, eol - tmp);
			size_t begin = content.find_first_not_of("\r\n", eol);
			size_t end = content.find(typeToken, begin);
			std::string source = content.substr(begin, ((end == std::string::npos) ? content.size() - 2 : end) - begin);
			pos = end;
			result[ShaderTypeFromString(type)] = source;
		}

		return result;
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const {
		glUseProgram(0);
	}

	uint32_t OpenGLShader::GetProgramId() const {
		return m_RendererID;
	};

	void OpenGLShader::SetInt(const std::string& name, const int value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* value, const uint32_t count) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, value);
	}

	void OpenGLShader::SetFloat3Array(const std::string& name, float* value, const uint32_t count) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3fv(location, count, value);
	}

	void OpenGLShader::SetFloat(const std::string& name, const float value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}
	
	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}
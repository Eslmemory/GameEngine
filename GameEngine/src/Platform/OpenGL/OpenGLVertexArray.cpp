#include "gepch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace GE {

	static GLenum ShaderDataTypeToOpenGLDataType(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Bool:     return GL_BOOL;
		}

		GE_ASSERT(false, "Unknown shader data type!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const {
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer) {
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		const BufferLayout& layout = vertexBuffer->GetLayout();
		int index = 0;
		for (auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, 
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLDataType(element.m_Type),
				element.m_Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.m_Offset
			);
			index++;
		}
		m_VertexBuffer.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer) {
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	const std::vector<std::shared_ptr<VertexBuffer>> OpenGLVertexArray::GetVertexBuffer() const {
		return m_VertexBuffer;
	}

	const std::shared_ptr<IndexBuffer> OpenGLVertexArray::GetIndexBuffer() const {
		return m_IndexBuffer;
	}

}
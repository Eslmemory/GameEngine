#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/Render/VertexArray.h"

namespace GE {

	class GE_API OpenGLVertexArray : public VertexArray{

	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffer() const override;
		virtual const std::shared_ptr<IndexBuffer> GetIndexBuffer() const override;
	
	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
	
}
#pragma once
#include "GameEngine/Render/Buffer.h"

namespace GE {

	class GE_API OpenGLVertexBuffer : public VertexBuffer{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void SetData(void* data, uint32_t size) override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		virtual const BufferLayout& GetLayout() const override { return m_Layout; };

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class GE_API OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		OpenGLIndexBuffer(uint32_t count);
		~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void SetData(void* data, uint32_t uint32_t) override;

		virtual uint32_t GetCount() const;

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}
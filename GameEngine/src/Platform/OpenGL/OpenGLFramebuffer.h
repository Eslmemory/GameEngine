#pragma once
#include "GameEngine/Render/Framebuffer.h"

namespace GE {

	class GE_API OpenGLFramebuffer : public Framebuffer {
	public:
		OpenGLFramebuffer() = default;
		OpenGLFramebuffer(const FramebufferSpecification& spec);

		virtual void Bind();
		virtual void UnBind();
		
		virtual uint32_t GetColorAttachmentRendererID(uint32_t index) override;
		virtual const FramebufferSpecification& GetSpecification() override { return m_Specification; }
		
		virtual void OnViewportResize(uint32_t width, uint32_t height);

		void Invalidate();

	private:
		uint32_t m_RendererID;
		FramebufferSpecification m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecification;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;

		uint32_t m_DepthAttachment;
		std::vector<uint32_t> m_ColorAttachments;

	};
}
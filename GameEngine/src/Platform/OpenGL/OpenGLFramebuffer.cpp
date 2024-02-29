#include "gepch.h"
#include "OpenGLFramebuffer.h"
#include <glad/glad.h>

namespace GE {

	namespace Utils {
		static void AttachmentColorTexture(uint32_t& id, uint32_t width, uint32_t height, GLenum internalFormat, GLenum format, uint32_t index) {
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glBindTexture(GL_TEXTURE_2D, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, id, 0);
		}

		static void AttachmentColorRenderBuffer(uint32_t& id, uint32_t width, uint32_t height, GLenum internalFormat, uint32_t index) {
			glGenRenderbuffers(1, &id);
			glBindRenderbuffer(GL_RENDERBUFFER, id);
			glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_RENDERBUFFER, id);
		}

		// static void AttachmentDepthTexture(uint32_t& id, uint32_t width, uint32_t height, GLenum attachmentType, uint32_t index) {
		// 	glGenTextures(1, &id);
		// 	glBindTexture(GL_TEXTURE_2D, id);
		// 	glTexStorage2D()
		// 
		// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// 
		// 	glBindTexture(GL_TEXTURE_2D, 0);
		// 	glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, id, 0);
		// }

		static void AttachmentDepthRenderBuffer(uint32_t& id, uint32_t width, uint32_t height) {
			glGenRenderbuffers(1, &id);
			glBindRenderbuffer(GL_RENDERBUFFER, id);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, id);
		}
	}

	static bool IsDepthFormat(FramebufferTextureFormat formate) {
		switch (formate) {
			case FramebufferTextureFormat::RGBA8: 
			case FramebufferTextureFormat::RED_INTEGER:
				return false;
				break;
		}
		return true;
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: m_Specification(spec) 
	{
		auto& attachments = m_Specification.m_Attachments.m_Attachments;
		for (int i = 0; i < attachments.size(); i++) {
			if (!IsDepthFormat(attachments[i].m_TextureFormate)) {
				m_ColorAttachmentSpecification.emplace_back(attachments[i]);
			}
			else
				m_DepthAttachmentSpecification = attachments[i];
		}

		Invalidate();
	}

	void OpenGLFramebuffer::Invalidate() {
		if (m_RendererID) {
			glDeleteFramebuffers(1, &m_RendererID);
			m_ColorAttachments.clear();
		}
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		
		// color attachment
		if (m_ColorAttachmentSpecification.size()) {

			for (size_t i = 0; i < m_ColorAttachmentSpecification.size(); i++) {
				m_ColorAttachments.resize(m_ColorAttachmentSpecification.size());
				switch (m_ColorAttachmentSpecification[i].m_TextureFormate) {
					case FramebufferTextureFormat::RGBA8:
						Utils::AttachmentColorTexture(m_ColorAttachments[i], m_Specification.m_Width, m_Specification.m_Height, GL_RGBA8, GL_RGBA, i);
						break;
					case FramebufferTextureFormat::RED_INTEGER:
						Utils::AttachmentColorRenderBuffer(m_ColorAttachments[i], m_Specification.m_Width, m_Specification.m_Height, GL_R32I, i);
						break;
				}
			}

		}

		// depth attachment
		if (m_DepthAttachmentSpecification.m_TextureFormate != FramebufferTextureFormat::None) {
			switch (m_DepthAttachmentSpecification.m_TextureFormate) {
				//case FramebufferTextureFormate::DEPTH32F_TEX3D:
				//	Utils::AttachmentDepthTexture(m_DepthAttachment, m_Specification.m_Width, m_Specification.m_Height, GL_RGBA8, GL_RGBA, i);
				//	break;
				case FramebufferTextureFormat::DEPTH24STENCIL8:
					Utils::AttachmentDepthRenderBuffer(m_DepthAttachment, m_Specification.m_Width, m_Specification.m_Height);
					break;
			}
		}

		if (m_ColorAttachments.size() > 1) {
			GE_CORE_ASSERT(m_ColorAttachments.size() <= 4);
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_ColorAttachments.size(), buffers);
		}
		else if (m_ColorAttachments.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}

		GE_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	void OpenGLFramebuffer::Bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		// glViewport是设置从[-1, 1]映射到[width, height]的函数
		glViewport(0, 0, m_Specification.m_Width, m_Specification.m_Height);
	}
	
	void OpenGLFramebuffer::UnBind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32_t OpenGLFramebuffer::GetColorAttachmentRendererID(uint32_t index) {
		GE_CORE_ASSERT(index < m_ColorAttachments.size());
		return m_ColorAttachments[index]; 
	}

	void OpenGLFramebuffer::OnViewportResize(uint32_t width, uint32_t height) {
		m_Specification.m_Width = width;
		m_Specification.m_Height = height;

		Invalidate();
	}
}
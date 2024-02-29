#pragma once
#include "GameEngine/Core/Core.h"
#include <vector>
#include <memory>

namespace GE {

	enum class FramebufferTextureFormat {
		None = 0,
		RGBA8,
		RED_INTEGER,
		DEPTH32F_TEX3D,
		DEPTH24STENCIL8
	};

	struct FramebufferTextureSpecification {
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat formate)
			: m_TextureFormate(formate) {}
		FramebufferTextureFormat m_TextureFormate = FramebufferTextureFormat::None;
	};

	struct FrameAttachmentSpecification {
		FrameAttachmentSpecification() = default;
		FrameAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			: m_Attachments(attachments) {}
		std::vector<FramebufferTextureSpecification> m_Attachments;
	};

	struct FramebufferSpecification {
		uint32_t m_Width, m_Height;
		FrameAttachmentSpecification m_Attachments;
		uint32_t Sampels = 1;
	};

	class GE_API Framebuffer {
	public:

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index) = 0;
		virtual const FramebufferSpecification& GetSpecification() = 0;
		
		virtual void OnViewportResize(uint32_t width, uint32_t height) = 0;

		static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& spec);
	};
}
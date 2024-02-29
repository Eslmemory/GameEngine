#pragma once
#include "GameEngine/Render/Texture.h"

namespace GE {

	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& filepath);
		virtual uint32_t GetWidth() override;
		virtual uint32_t GetHeight() override;
		virtual uint32_t GetRendererID() override;

		virtual void Bind(uint32_t slot) override;
		virtual void UnBind() override;

		virtual void SetData(void* data, uint32_t size) override;

	private:
		int m_Width, m_Height, m_Channel;
		int m_Internalformat, m_ImageFormat;
		unsigned int m_RendererID;
	};

	class OpenGLCubeMapTexture : public CubeMapTexture {
	public:
		OpenGLCubeMapTexture();
		OpenGLCubeMapTexture(uint32_t width, uint32_t height);

		virtual uint32_t GetWidth() override { return m_Width; };
		virtual uint32_t GetHeight() override { return m_Height; };
		virtual void Bind(uint32_t slot = 0) override;
		virtual void UnBind() override;
		virtual void SetFace(FaceTarget faceIndex, const std::string& path);
		virtual void GenerateMap();
		virtual void Generate();

		virtual uint32_t GetRendererID() { return m_RendererID; }
		virtual void SetData(void* data, uint32_t size) {}

	private:
		uint32_t m_RendererID;
		uint32_t m_Width, m_Height;
		std::vector<std::string> m_Paths;
	};
}
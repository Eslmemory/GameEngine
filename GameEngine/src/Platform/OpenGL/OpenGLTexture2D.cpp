#include "gepch.h"
#include "OpenGLTexture2D.h"
#include <stb_image.h>
#include <glad/glad.h>

namespace GE {
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		m_Internalformat = GL_RGBA8;
		m_ImageFormat = GL_RGBA;;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		// glGenerateMipmap(GL_TEXTURE_2D);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath) {
		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_Channel, 0);
		if (data) {

			int internalformat = 0, imageFormat = 0;
			if (m_Channel == 3) {
				imageFormat = GL_RGB;
				internalformat = GL_RGB8;
			}
			else if (m_Channel == 4) {
				imageFormat = GL_RGBA;
				internalformat = GL_RGBA8;
			}
			m_Internalformat = internalformat;
			m_ImageFormat = imageFormat;
			GE_CORE_ASSERT(false, "Format not supported! ");

			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, m_Internalformat, m_Width, m_Height, 0, m_ImageFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);
		}
		else {
			throw "Failed to load texture! ";
		}
	}

	void OpenGLTexture2D::Bind(uint32_t slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void OpenGLTexture2D::UnBind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size) {
		uint32_t bpp = m_ImageFormat == GL_RGBA ? 4 : 3;
		GE_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_ImageFormat, GL_UNSIGNED_BYTE, data);
	}

	uint32_t OpenGLTexture2D::GetWidth() {
		return m_Width;
	}

	uint32_t OpenGLTexture2D::GetHeight() {
		return m_Height;
	}

	uint32_t OpenGLTexture2D::GetRendererID() {
		return m_RendererID;
	}

	OpenGLCubeMapTexture::OpenGLCubeMapTexture() {
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

		m_Width = 512;
		m_Height = 512;

		for (uint32_t i = 0; i < 6; i++) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, m_Width, m_Height, 0, GL_RGB, GL_FLOAT, nullptr);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	OpenGLCubeMapTexture::OpenGLCubeMapTexture(uint32_t width, uint32_t height) 
		:m_Width(width), m_Height(height)
	{
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

		for (unsigned int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, m_Width, m_Height, 0, GL_RGB, GL_FLOAT, nullptr);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void OpenGLCubeMapTexture::Bind(uint32_t slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
	}

	void OpenGLCubeMapTexture::UnBind() {
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void OpenGLCubeMapTexture::SetFace(FaceTarget faceIndex, const std::string& path) {
		m_Paths[(uint32_t)faceIndex] = path;
	}

	void OpenGLCubeMapTexture::GenerateMap() {
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}

	void OpenGLCubeMapTexture::Generate() {
		
	}

}
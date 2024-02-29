#pragma once
#include "GameEngine/Render/Texture.h"
#include "GameEngine/Core/Log.h"
#include "GameEngine/Render/Shader.h"

namespace GE {

	class RayTrace {
	public:
		RayTrace();
		void DrawBackground(glm::mat4& viewProjection);

	public:
		uint32_t m_Width = 512, m_Height = 512;
		std::shared_ptr<CubeMapTexture> m_CubeMapTexture;
		std::shared_ptr<Shader> m_Equirec2CubeMapShader;
		std::shared_ptr<Shader> m_BackgroundShader;
		std::shared_ptr<Texture2D> m_EquirectangularTexture;
	};
}
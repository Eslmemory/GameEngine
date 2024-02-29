#pragma once
#include "GameEngine/Core/Core.h"

namespace GE {

	class GE_API Texture {
	public:

		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;
		virtual uint32_t GetRendererID() = 0;

		virtual void Bind(uint32_t slot) = 0;
		virtual void UnBind() = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		bool operator==(Texture& texture1) {
			return this->GetRendererID() == texture1.GetRendererID();
		}
	};

	class GE_API Texture2D : public Texture {
	public:
		static std::shared_ptr<Texture2D> Create(uint32_t width, uint32_t height);
		static std::shared_ptr<Texture2D> Create(const std::string& filepath);
		static std::shared_ptr<Texture2D> Create(const std::filesystem::path& filepath);
	};

	enum class FaceTarget : uint32_t {
		Right = 0,
		Left = 1,
		Top = 2,
		Bottom = 3,
		Front = 4,
		Back = 5
	};

	class CubeMapTexture : public Texture {
	public:
		static std::shared_ptr<CubeMapTexture> Create();
		static std::shared_ptr<CubeMapTexture> Create(uint32_t width, uint32_t height);
		virtual void SetFace(FaceTarget faceIndex, const std::string& path) = 0;
		virtual void GenerateMap() = 0;
		virtual void Generate() = 0;

	};
	// 2634

}
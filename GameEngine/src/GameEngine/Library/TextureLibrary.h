#pragma once
#include "Library.h"
#include "GameEngine/Render/Texture.h"

namespace GE {
	template<>
	class Library<Texture2D> : public LibraryBase<Library, Texture2D> {
	public:
		Library();
		std::shared_ptr<Texture2D> GetWhiteTexture();
		std::shared_ptr<Texture2D> GetBlackTexture();
		std::shared_ptr<Texture2D> GetDefaultTexture();
		std::shared_ptr<Texture2D> GetDefaultNormalTexture();
	};
}
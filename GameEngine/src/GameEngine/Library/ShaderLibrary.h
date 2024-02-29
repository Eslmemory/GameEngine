#pragma once
#include "Library.h"
#include "GameEngine/Render/Shader.h"

namespace GE {
	template<>
	class Library<Shader> : public LibraryBase<Library, Shader> {
	public:
		Library();
		std::shared_ptr<Shader> GetDefaultShader();
	};
}
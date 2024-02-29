#pragma once
#include "GameEngine.h"
#include "GameEngine/Core/PublicSingleton.h"

#include <string>
#include <unordered_map>

namespace GE {
	class IconManager : public Singleton<IconManager> {
	public:
		IconManager();
		~IconManager() = default;

		std::shared_ptr<Texture2D> FindOrLoadTexture(const std::string& path) {
			if (m_IconLibrary.find(path) != m_IconLibrary.end())
				return m_IconLibrary[path];

			m_IconLibrary[path] = Texture2D::Create(path);
			return m_IconLibrary[path];
		}

		void Add(const std::string& path, const std::shared_ptr<Texture2D> texture) {
			GE_ASSERT(m_IconLibrary.find(path) == m_IconLibrary.end(), "Texture has exited! ");
			m_IconLibrary[path] = texture;
		}

		std::shared_ptr<Texture2D> Get(const std::string& path) {
			GE_ASSERT(m_IconLibrary.find(path) != m_IconLibrary.end(), "Texture is not existed! ");
			return m_IconLibrary[path];
		}
	
	private:
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_IconLibrary;
	};

}
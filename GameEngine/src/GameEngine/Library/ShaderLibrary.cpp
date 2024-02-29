#include "gepch.h"
#include "ShaderLibrary.h"
#include "GameEngine/Manager/ConfigManager.h"

namespace GE {
	
	Library<Shader>::Library() {
		Add("PBRShader", Shader::Create(ConfigManager::GetInstance().GetAssetFolder() / "Shader/PBR.glsl"));
		Add("PBRShader", Shader::Create(ConfigManager::GetInstance().GetAssetFolder() / "Shader/PBR.glsl"));
		Add("PBRShader", Shader::Create(ConfigManager::GetInstance().GetAssetFolder() / "Shader/PBR.glsl"));
	
	}

	std::shared_ptr<Shader> Library<Shader>::GetDefaultShader() {
		return Get("PBRShader");
	}
}

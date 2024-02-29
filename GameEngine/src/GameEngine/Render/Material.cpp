#include "gepch.h"
#include "Material.h"

namespace GE {

	void Material::Initialize() {
		
		unsigned char data[4];

		// set metaillic
		for (uint32_t i = 0; i < 3; i++) {
			data[i] = (unsigned char)(255.0f * metallic);
		}
		data[3] = (unsigned char)255.0f;
		metallicRGBA->SetData(data, sizeof(unsigned char) * 4);

		// set roughness
		for (uint32_t i = 0; i < 3; i++) {
			data[i] = (unsigned char)(255.0f * roughness);
		}
		data[3] = (unsigned char)255.0f;
		roughnessRGBA->SetData(data, sizeof(unsigned char) * 4);
	}

}
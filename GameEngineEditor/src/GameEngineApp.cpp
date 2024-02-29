#include <iostream>
#include "GameEngine.h"
#include "GameEngine/Core/Entrypoint.h"
#include "EditorLayer.h"

namespace GE {


	class GameEngineEditor : public Application {

	public:
		GameEngineEditor(std::string name)
			: Application(name)
		{
			PushLayer(new EditorLayer("Editor"));
		};

		~GameEngineEditor() {

		};
	};

	Application* CreateApplication() {
		return new GameEngineEditor("Engine Editor");
	}

}



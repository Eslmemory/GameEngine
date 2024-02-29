#pragma once
#include "GameEngine/Core/Application.h"
#include "GameEngine/Core/Log.h"

extern GE::Application* GE::CreateApplication();

int main(int argc, char** argv) {

	GE::Log::Init();
	auto app = GE::CreateApplication();
	app->run();
	delete app;

	return 0;
}
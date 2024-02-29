#include "gepch.h"
#include <GLFW/glfw3.h>
#include "WindowInput.h"
#include "GameEngine/Core/Application.h"

namespace GE {

	Input* Input::s_Input = new WindowInput();

	bool WindowInput::IsMouseButtonPressedImpl(int button) {
		auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	bool WindowInput::IsKeyPressedImpl(int keycode) {
		auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> WindowInput::GetMousePositionImpl() {
		double xpos, ypos;
		auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float WindowInput::GetMouseXImpl() {
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowInput::GetMouseYImpl() {
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}
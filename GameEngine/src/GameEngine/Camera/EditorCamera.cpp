#include "gepch.h"
#include "EditorCamera.h"
#include "GameEngine/Core/Log.h"
#include "GameEngine/Core/Input.h"
#include "GameEngine/Core/KeyCodes.h"
#include "GameEngine/Core/MouseButtonCodes.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "glad/glad.h"

namespace GE {

	EditorCamera::EditorCamera(float width, float height)
		: m_Width(width), m_Height(height)
	{
		UpdateProjectionMatrix();
		UpdateViewMatrix();
	}

	glm::quat EditorCamera::GetOrientation() const {
		return glm::quat(glm::vec3(m_Pitch, m_Yaw, 0.0f));
	}

	glm::vec3 EditorCamera::GetUpDirection() const {
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 EditorCamera::GetRightDirection() const {
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 EditorCamera::GetForwardDirection() const {
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 EditorCamera::CalculatePosition() {
		return m_FocalPoint - m_Distance * GetForwardDirection();
	}

	void EditorCamera::UpdateProjectionMatrix() {
		m_ProjectionMatrix = glm::perspective(glm::radians(60.0f), m_Width / m_Height, m_NearPlane, m_FarPlane);
	}

	void EditorCamera::UpdateViewMatrix() {
		m_CameraPosition = CalculatePosition();

		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_CameraPosition) * glm::toMat4(GetOrientation());
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	bool EditorCamera::MouseScrolled(MouseScrollEvent& event) {
		float delta = (float)event.GetYOffset() * 100;
		MouseZoom(delta);
		UpdateViewMatrix();
		return false;
	}

	void EditorCamera::OnEvent(Event& event) {
		EventDispatcher dispatch(event);
		dispatch.Dispatch<MouseScrollEvent>(BIND_FUNC(EditorCamera, MouseScrolled));
	}

	void EditorCamera::OnUpdate() {

		if (Input::IsKeyPressed(GE_KEY_LEFT_ALT)) {
			glm::vec2 mouse{ Input::GetMouseX(), Input::GetMouseY() };
			if ((Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_LEFT) ||
				Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_MIDDLE) ||
				Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_RIGHT)) && !m_MousePressedInit) {
				m_MouseInitPosition = mouse;
				m_MousePressedInit = true;
			}

			glm::vec2 delta(mouse.x - m_MouseInitPosition.x, mouse.y - m_MouseInitPosition.y);
			m_MouseInitPosition = mouse;

			if (Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_LEFT)) {
				MouseRotate(delta);
			}
			else if (Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_MIDDLE)) {
				MousePan(delta);
			}
			else if (Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_RIGHT)) {
				MouseZoom(delta.y);
			}
		}
		else if (Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_RIGHT)) {
			if (Input::IsKeyPressed(GE_KEY_W)) {
				m_FocalPoint += 0.003f * m_MoveSpeed * GetForwardDirection();
			}
			else if (Input::IsKeyPressed(GE_KEY_S)) {
				m_FocalPoint -= 0.003f * m_MoveSpeed * GetForwardDirection();
			}
			else if (Input::IsKeyPressed(GE_KEY_A)) {
				m_FocalPoint -= 0.003f * m_MoveSpeed * GetRightDirection();
			}
			else if (Input::IsKeyPressed(GE_KEY_D)) {
				m_FocalPoint += 0.003f * m_MoveSpeed * GetRightDirection();
			}
			else if (Input::IsKeyPressed(GE_KEY_Q)) {
				m_FocalPoint -= 0.003f * m_MoveSpeed * GetUpDirection();
			}
			else if (Input::IsKeyPressed(GE_KEY_E)) {
				m_FocalPoint += 0.003f * m_MoveSpeed * GetUpDirection();
			}

			if (Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_RIGHT)) {
				glm::vec2 mouse(Input::GetMouseX(), Input::GetMouseY());
				if (!m_MousePressedInit) {
					m_MouseInitPosition = mouse;
					m_MousePressedInit = true;
				}
				glm::vec2 delta(mouse.x - m_MouseInitPosition.x, mouse.y - m_MouseInitPosition.y);
				m_MouseInitPosition = mouse;
				MouseRotate(delta);
			}
		}
		else {
			m_MousePressedInit = false;
		}
		UpdateViewMatrix();
	}

	void EditorCamera::MousePan(glm::vec2 delta) {
		
		// 这里一个加一个减是因为窗口的坐标系是右下，因此delta算出来往下走才是正数
		m_FocalPoint -= 0.003f * delta.x * m_MoveSpeed * GetRightDirection() * m_Distance;
		m_FocalPoint += 0.003f * delta.y * m_MoveSpeed * GetUpDirection() * m_Distance;
	}

	void EditorCamera::MouseRotate(glm::vec2 delta) {
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw -= yawSign * 0.003f * delta.x * m_RotateSpeed;
		m_Pitch -= 0.003f * delta.y * m_RotateSpeed;
	}

	void EditorCamera::MouseZoom(float delta) {
		m_Distance -= 0.003f * delta * m_ZoomSpeed;
		if (m_Distance < 1.0f) {
			// m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}
	}

}
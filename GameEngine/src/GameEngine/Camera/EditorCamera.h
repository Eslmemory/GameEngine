#pragma once
#include "Camera.h"
#include "GameEngine/Event/MouseEvent.h"

namespace GE {

	class GE_API EditorCamera : public Camera {
	public:
		EditorCamera() = default;
		EditorCamera(float width, float height);

		glm::vec3 CalculatePosition();
		void UpdateViewMatrix();
		void UpdateProjectionMatrix();

		glm::quat GetOrientation() const;
		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;

		void SetViewport(float width, float height) { m_Width = width; m_Height = height; UpdateProjectionMatrix(); }
		void SetCameraFocalPoint(glm::vec3& postion) { m_FocalPoint = postion; }
		void SetCameraDistance(float distance) { m_Distance = distance; }

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjection() const { return m_ProjectionMatrix; }
		virtual glm::mat4 GetViewProjectionMatrix() const { return m_ProjectionMatrix * m_ViewMatrix; }

		glm::vec3 GetCameraPosition() const { return m_CameraPosition; }
		float GetWidth() const { return m_Width; }
		float GetHeight() const { return m_Height; }
		float GetDistance() const { return m_Distance; }
		float GetPitch() const { return m_Pitch; }
		float GetYaw() const { return m_Yaw; }
		float GetFov() const { return m_Fov; }
		float GetAspectRatio() const { return m_AspectRatio; }
		float GetNearClip() const { return m_NearPlane; }
		float GetFarClip() const { return m_FarPlane; }

		void SetFov(const float fov) { m_Fov = fov; UpdateProjectionMatrix(); }
		void SetNearClip(const float nearClip) { m_NearPlane = nearClip; UpdateProjectionMatrix(); }
		void SetFarClip(const float farClip) { m_FarPlane = farClip; UpdateProjectionMatrix(); }

		void OnUpdate();
		void OnEvent(Event& event);

		bool MouseScrolled(MouseScrollEvent& event);

		void MousePan(glm::vec2 delta);
		void MouseRotate(glm::vec2 delta);
		void MouseZoom(float delta);
	
	private:
		glm::mat4 m_ViewMatrix, m_ProjectionMatrix;
		glm::vec3 m_FocalPoint = { 0, 0, 0 };
		glm::vec3 m_CameraPosition = { 0, 0, 0 };
		float m_Distance = 10.0f;
		float m_Pitch = 0.0f;
		float m_Yaw = 0.0f;
		// yaw和pitch会一直保存着旋转的状态，一直是相对于起始的状态，而不是相对上一帧的

	private:
		float m_Width = 1280, m_Height = 720;
		float m_Fov = 45.0f, m_NearPlane = 0.1f, m_FarPlane = 100.0f, m_AspectRatio = 1.778f;

	private:
		bool m_MousePressedInit = false;
		glm::vec2 m_MouseInitPosition = { 0.0f, 0.0f };
		float m_MoveSpeed = 0.8f;
		float m_RotateSpeed = 1.0f;
		float m_ZoomSpeed = 1.0f;
	};
}
#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: m_Position(position), m_Front(glm::vec3(0.0f)), m_Up(glm::vec3(0.0f)), m_Right(glm::vec3(0.0f)), m_WorldUp(up), m_Yaw(yaw),
	m_Pitch(pitch), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM)
{
	UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: m_Position(glm::vec3(posX, posY, posZ)), m_Front(glm::vec3(0.0f)), m_Up(glm::vec3(0.0f)), m_Right(glm::vec3(0.0f)),
	m_WorldUp(glm::vec3(upX, upY, upZ)), m_Yaw(yaw), m_Pitch(pitch), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM)
{
	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
	float velocity = m_MovementSpeed * deltaTime;
	switch (direction) {
	case CameraMovement::Forward:
		m_Position += m_Front * velocity;
		break;
	case CameraMovement::Backward:
		m_Position -= m_Front * velocity;
		break;
	case CameraMovement::Left:
		m_Position -= m_Right * velocity;
		break;
	case CameraMovement::Right:
		m_Position += m_Right * velocity;
		break;
	}
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
	xOffset *= m_MouseSensitivity;
	yOffset += m_MouseSensitivity;

	m_Yaw += xOffset;
	m_Pitch += yOffset;

	if (constrainPitch)
	{
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
	}

	UpdateCameraVectors();

}

void Camera::ProcessMouseScroll(float yOffset)
{
	m_Zoom -= static_cast<float>(yOffset);
	if (m_Zoom < 1.0f)
		m_Zoom = 1.0f;
	if (m_Zoom > 45.0f)
		m_Zoom = 45.0f;
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

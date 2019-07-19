#include "Camera.h"
#include <gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position /*= glm::vec3(0.f, 0.f, 0.f)*/, glm::vec3 up /*= glm::vec3(0.f, 1.f, 0.f)*/, float yaw /*= YAW*/, float pitch /*= PITCH*/)
	: Front(glm::vec3(0.f, 0.f, -1.f)),
	MovementSpeed(SPEED),
	MouseSensitivity(SENSITIVITY),
	Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: Front(glm::vec3(0.f, 0.f, -1.f)),
	MovementSpeed(SPEED),
	MouseSensitivity(SENSITIVITY),
	Zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

glm::mat4 Camera::getLookAtView()
{
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::processKeyBoard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	switch (direction)
	{
	case FORWARD:
		Position += Front * velocity;
		break;
	case BACKWARD:
		Position -= Front * velocity;
		break;
	case LEFT:
		Position -= Right * velocity;
		break;
	case RIGHT:
		Position += Right * velocity;
		break;
	default:
		break;
	}
	updateCameraVectors();
}

void Camera::processMouseMove(float xoffset, float yoffset, bool constrainPitch /*= true*/)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch >= 89.f)
			Pitch = 89.f;
		if (Pitch <= -89.f)
			Pitch = -89.f;
	}
	updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
	if (Zoom >= 1.f && Zoom < 45.f)
		Zoom -= yoffset;
	if (Zoom <= 1.f)
		Zoom = 1.f;
	if (Zoom >= 45.f)
		Zoom = 45.f;
}

void Camera::updateCameraVectors()
{
	glm::vec3 tmpFront;
	tmpFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	tmpFront.y = sin(glm::radians(Pitch));
	tmpFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(tmpFront);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

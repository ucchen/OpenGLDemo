#include "Camera.h"

Camera::Camera(glm::vec3 position /*= glm::vec3(0.f, 0.f, 0.f)*/, glm::vec3 up /*= glm::vec3(0.f, 1.f, 0.f)*/, float yaw /*= YAW*/, float pitch /*= PITCH*/)
	: front(glm::vec3(0.f, 0.f, -1.f)),
	movementSpeed(SPEED),
	mouseSensitivity(SENSITIVITY),
	zoom(ZOOM)
{
	position = position;
	yaw = yaw;
	pitch = pitch;
	updateCameraVector();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: front(glm::vec3(0.f, 0.f, -1.f)),
	movementSpeed(SPEED),
	mouseSensitivity(SENSITIVITY),
	zoom(ZOOM)
{
	position = glm::vec3(posX, posY, posZ);
	yaw = yaw;
	pitch = pitch;
	updateCameraVector();
}

void Camera::processKeyBoard(Camera_Movement direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	switch (direction)
	{
	case FORWARD:
		position += front * velocity;
		break;
	case BACKWARD:
		position -= front * velocity;
		break;
	case LEFT:
		position -= right * velocity;
		break;
	case RIGHT:
		position += right * velocity;
		break;
	default:
		break;
	}
	updateCameraVector();
}

void Camera::processMouseMove(float xoffset, float yoffset, bool constrainPitch /*= true*/)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (constrainPitch)
	{
		if (pitch >= 89.f)
			pitch = 89.f;
		if (pitch <= -89.f)
			pitch = -89.f;
	}
	updateCameraVector();
}

void Camera::updateCameraVector()
{

}

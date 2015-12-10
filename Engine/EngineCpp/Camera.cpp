#include "Camera.h"
#include "BoundingFrustum.h"
#include <glm\gtc\matrix_transform.hpp>
#include "Window.h"

CommonObjects::Camera::Camera()
{
	fovDegrees = 60;
	position = glm::dvec3();
	if (&Render::Window::GetActiveWindow() != NULL)
	{
		ProjectionMatrix = glm::perspective(static_cast<float>(glm::radians(fovDegrees)), Render::Window::GetActiveWindow().GetAspectRatio(), 0.1f, 1000000.0f);
		ViewMatrix = glm::mat4x4();
		frustum = BoundingVolume::BoundingFrustum(ProjectionMatrix, position);
	}
}

CommonObjects::Camera::~Camera()
{
}

double CommonObjects::Camera::GetFOVdegrees() const
{
	return fovDegrees;
}

double CommonObjects::Camera::GetFOVradians() const
{
	return fovDegrees * 0.01745329251994329576923690768489;
}

BoundingVolume::BoundingFrustum CommonObjects::Camera::GetFrustum() const
{
	return frustum;
}

glm::dvec3 CommonObjects::Camera::GetPosition() const
{
	return position;
}

glm::mat4x4 CommonObjects::Camera::GetViewMatrix() const
{
	return ViewMatrix;
}

glm::mat4x4 CommonObjects::Camera::GetProjectionMatrix() const
{
	return ProjectionMatrix;
}

void CommonObjects::Camera::SetPosition(glm::dvec3 pos)
{
	position = pos;
	frustum = BoundingVolume::BoundingFrustum(ProjectionMatrix * ViewMatrix, position);
}

void CommonObjects::Camera::SetViewMatrix(glm::mat4x4 matrix)
{
	ViewMatrix = matrix;
	frustum = BoundingVolume::BoundingFrustum(ProjectionMatrix * ViewMatrix, position);
}
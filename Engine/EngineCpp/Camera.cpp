#include "Camera.h"
#include "Game.h"
#include "WindowManager.h"
#include "BoundingSphere.h"
#include <glm\gtc\matrix_transform.hpp>

Camera::Camera()
{
	FieldOfView_degrees = 60;
	Position = glm::dvec3();
	Projection = glm::perspective(static_cast<float>(FieldOfView_degrees), Game::GetWindowManager().GetAspectRatio(), 0.1f, 1000000.0f);
	View = glm::mat4x4();
}

Camera::~Camera()
{

}

bool Camera::BoundingSphereInFrustum(const BoundingSphere& sphere)
{
	return true;
}

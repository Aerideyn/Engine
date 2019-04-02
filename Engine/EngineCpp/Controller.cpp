#include "Controller.h"
#include "Camera.h"

Controller::Controller()
{
	ViewMatrix = glm::mat4x4();
	Position = glm::dvec3(0.0,0.0,500000.0);
}

Controller::~Controller()
{

}

void Controller::Update(double DeltaT)
{
	if (auto cam = ptr_AttachedCamera.lock())
	{
		cam->SetViewMatrix(ViewMatrix);
		cam->SetPosition(Position);
	}
}
void Controller::AttachCamera(std::shared_ptr<Camera> camera)
{
	ptr_AttachedCamera = camera;
}
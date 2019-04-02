#pragma once
#include "Controller.h"
#include <glm/glm.hpp>

class Camera;

class FPSController : public Controller
{
private:

	double updownRot = 0.0f;
	double leftrightRot = 0.0f;

	double moveSpeed = 27.0;
	double lookSpeed = 0.1;

	void UpdateViewMatrix(double deltaTime);
	void UpdatePosition(double deltaTime);

public:
	FPSController();
	~FPSController();

	glm::mat4x4 GetViewMatrix();

	void Update(double DeltaT);
};


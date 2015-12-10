#pragma once
#include "Controller.h"
#include <glm/glm.hpp>
namespace CommonObjects
{
	class FPSController : public Controller
	{
	public:
		FPSController();
		~FPSController();
	private:
		double updownRot = 0.0f;
		double leftrightRot = 0.0f;
		double moveSpeed = 270;
		double lookSpeed = 0.1;
		void UpdateViewMatrix(double deltaTime);
		void UpdatePosition(double deltaTime);

	public:
		void SetMovementSpeed(double speed) { moveSpeed = speed; };
		glm::mat4x4 GetViewMatrix() { return ViewMatrix; };
		void Update(double DeltaT);
	};
}

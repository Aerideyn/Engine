#include "FPSController.h"

#include "game.h"
#include "InputService.h"
#include "WindowManager.h"
#include <glm/gtc/matrix_transform.hpp>

const float PiONTwo = 1.5707963267948966192313216916398f;

FPSController::FPSController()
{

}

FPSController::~FPSController()
{

}

void FPSController::UpdateViewMatrix(double deltaTime)
{
	glm::ivec2 mouseP = Game::GetInputService().GetMousePosition();
	glm::ivec2 Size = Game::GetWindowManager().GetWindowSize();

	double SizeX = static_cast<double>(Size.x) / 2.0;
	double SizeY = static_cast<double>(Size.y) / 2.0;

	double xDifference = static_cast<double>(mouseP.x) - SizeX;
	double yDifference = static_cast<double>(mouseP.y) - SizeY;

	if ((updownRot - (lookSpeed * yDifference * deltaTime) > -PiONTwo) && (updownRot - (lookSpeed * yDifference * deltaTime) < PiONTwo))
		updownRot -= (lookSpeed * yDifference * deltaTime);

	leftrightRot -= (lookSpeed * xDifference * deltaTime);
	Game::GetInputService().SetMousePosition(Size / 2);
	
	//////

	glm::vec4 cameraOriginalTarget(0, 0, -1, 1);
	glm::vec4 cameraOriginalUpVector(0, 1, 0,0);

	glm::mat4x4 RotationX = glm::rotate(glm::mat4x4(), static_cast<float>(glm::degrees(updownRot)), glm::vec3(1, 0, 0));
	glm::mat4x4 RotationY = glm::rotate(glm::mat4x4(), static_cast<float>(glm::degrees(leftrightRot)), glm::vec3(0, 1, 0));

	glm::mat4x4 cameraRotation = RotationY * RotationX;

	glm::vec4 cameraFinalTarget = cameraRotation * cameraOriginalTarget;

	glm::vec4 cameraRotatedUpVector = cameraRotation * cameraOriginalUpVector;

	ViewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(cameraFinalTarget.x, cameraFinalTarget.y, cameraFinalTarget.z), glm::vec3(cameraRotatedUpVector.x, cameraRotatedUpVector.y, cameraRotatedUpVector.z));
}

void FPSController::UpdatePosition(double deltaTime)
{
	glm::vec4 moveVector(0, 0, 0, 1);
	InputService& input = Game::GetInputService();

	if (input.IsKeyPressed(InputServiceKey::Up) || input.IsKeyPressed(InputServiceKey::W))
		moveVector += glm::vec4(0, 0, -1, 0);
	if (input.IsKeyPressed(InputServiceKey::Down) || input.IsKeyPressed(InputServiceKey::S))
		moveVector += glm::vec4(0, 0, 1, 0);
	if (input.IsKeyPressed(InputServiceKey::Right) || input.IsKeyPressed(InputServiceKey::D))
		moveVector += glm::vec4(1, 0, 0, 0);
	if (input.IsKeyPressed(InputServiceKey::Left) || input.IsKeyPressed(InputServiceKey::A))
		moveVector += glm::vec4(-1, 0, 0, 0);
	if (input.IsKeyPressed(InputServiceKey::Q))
		moveVector += glm::vec4(0, 1, 0, 0);
	if (input.IsKeyPressed(InputServiceKey::Z))
		moveVector += glm::vec4(0, -1, 0, 0);

	if (input.IsKeyPressed(InputServiceKey::Add))
		moveSpeed *= 1.005;
	if (input.IsKeyPressed(InputServiceKey::Subtract))
		moveSpeed *= 0.995;

	moveVector = moveVector * ViewMatrix;

	glm::dvec3 VectorToAdd = glm::dvec3(moveVector.x, moveVector.y, moveVector.z) * moveSpeed * deltaTime;
	Position += VectorToAdd;
}

void FPSController::Update(double deltaTime)
{
	UpdateViewMatrix(deltaTime);
	UpdatePosition(deltaTime);
	Controller::Update(deltaTime);
}

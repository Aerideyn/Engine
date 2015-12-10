#include "FPSController.h"
#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

const float PiONTwo = 1.5707963267948966192313216916398f;

CommonObjects::FPSController::FPSController()
{

}

CommonObjects::FPSController::~FPSController()
{

}

void CommonObjects::FPSController::UpdateViewMatrix(double deltaTime)
{
	glm::dvec2 mouseP = Services::Mouse::GetMousePosition();
	Render::Window& activeWindow = Render::Window::GetActiveWindow();

	double SizeX = static_cast<double>(activeWindow.GetWidthX()) / 2.0;
	double SizeY = static_cast<double>(activeWindow.GetWidthY()) / 2.0;

	double xDifference = static_cast<double>(mouseP.x) - SizeX;
	double yDifference = static_cast<double>(mouseP.y) - SizeY;

	if ((updownRot - (lookSpeed * yDifference * deltaTime) > -PiONTwo) && (updownRot - (lookSpeed * yDifference * deltaTime) < PiONTwo))
		updownRot -= (lookSpeed * yDifference * deltaTime);

	leftrightRot -= (lookSpeed * xDifference * deltaTime);
	Services::Mouse::SetMousePosition(SizeX, SizeY);

	//////

	glm::vec4 cameraOriginalTarget(0, 0, -1, 1);
	glm::vec4 cameraOriginalUpVector(0, 1, 0, 0);

	glm::mat4x4 RotationX = glm::rotate(glm::mat4x4(), static_cast<float>(updownRot), glm::vec3(1, 0, 0));
	glm::mat4x4 RotationY = glm::rotate(glm::mat4x4(), static_cast<float>(leftrightRot), glm::vec3(0, 1, 0));

	glm::mat4x4 cameraRotation = RotationY * RotationX;

	glm::vec4 cameraFinalTarget = cameraRotation * cameraOriginalTarget;

	glm::vec4 cameraRotatedUpVector = cameraRotation * cameraOriginalUpVector;

	ViewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(cameraFinalTarget.x, cameraFinalTarget.y, cameraFinalTarget.z), glm::vec3(cameraRotatedUpVector.x, cameraRotatedUpVector.y, cameraRotatedUpVector.z));
}

void CommonObjects::FPSController::UpdatePosition(double deltaTime)
{
	glm::vec4 moveVector(0, 0, 0, 1);

	if (Services::Keyboard::IsKeyDown(Services::KeyboardKey::Up) || Services::Keyboard::IsKeyDown(Services::KeyboardKey::W))
		moveVector += glm::vec4(0, 0, -1, 0);
	if (Services::Keyboard::IsKeyDown(Services::KeyboardKey::Down) || Services::Keyboard::IsKeyDown(Services::KeyboardKey::S))
		moveVector += glm::vec4(0, 0, 1, 0);
	if (Services::Keyboard::IsKeyDown(Services::KeyboardKey::Right) || Services::Keyboard::IsKeyDown(Services::KeyboardKey::D))
		moveVector += glm::vec4(1, 0, 0, 0);
	if (Services::Keyboard::IsKeyDown(Services::KeyboardKey::Left) || Services::Keyboard::IsKeyDown(Services::KeyboardKey::A))
		moveVector += glm::vec4(-1, 0, 0, 0);
	if (Services::Keyboard::IsKeyDown(Services::KeyboardKey::Q))
		moveVector += glm::vec4(0, 1, 0, 0);
	if (Services::Keyboard::IsKeyDown(Services::KeyboardKey::Z))
		moveVector += glm::vec4(0, -1, 0, 0);

	if (Services::Keyboard::IsKeyDown(Services::KeyboardKey::Add))
	{
		moveSpeed *= 1.005;
		std::cout << moveSpeed << std::endl;
	}
	if (Services::Keyboard::IsKeyDown(Services::KeyboardKey::Subtract))
	{
		moveSpeed *= 0.995;
		std::cout << moveSpeed << std::endl;
	}
	moveVector = moveVector * ViewMatrix;

	glm::dvec3 VectorToAdd = glm::dvec3(moveVector.x, moveVector.y, moveVector.z) * moveSpeed * deltaTime;
	Position += VectorToAdd;
}

void CommonObjects::FPSController::Update(double deltaTime)
{
	UpdateViewMatrix(deltaTime);
	UpdatePosition(deltaTime);
	Controller::Update(deltaTime);
}

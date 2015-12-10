#include "Mouse.h"
#include "Window.h"
#include <GLFW\glfw3.h>

Services::Mouse::Mouse()
{
}


Services::Mouse::~Mouse()
{
}

glm::dvec2 Services::Mouse::GetMousePosition()
{
	double x = -1; double y = -1;
	glfwGetCursorPos(Render::Window::GetActiveWindow().windowHandle, &x, &y);
	return glm::dvec2(x, y);
}

void Services::Mouse::SetMousePosition(double X, double Y)
{
	glfwSetCursorPos(Render::Window::GetActiveWindow().windowHandle, X, Y);
}

bool Services::Mouse::LeftMouseButtonDown()
{
	return glfwGetMouseButton(Render::Window::GetActiveWindow().windowHandle, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

bool Services::Mouse::RightMouseButtonDown()
{
	return glfwGetMouseButton(Render::Window::GetActiveWindow().windowHandle, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}
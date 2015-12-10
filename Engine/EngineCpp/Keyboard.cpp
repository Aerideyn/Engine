#include "Keyboard.h"
#include "Window.h"
#include <GLFW\glfw3.h>

Services::Keyboard::Keyboard()
{
}


Services::Keyboard::~Keyboard()
{
}

bool Services::Keyboard::IsKeyDown(Services::KeyboardKey::KeyboardKey key)
{
	int result = glfwGetKey(Render::Window::GetActiveWindow().windowHandle, key);
	return result == GLFW_PRESS;
}
#include "Timer.h"
#include "GLFW\glfw3.h"

Services::Timer::Timer()
{
}


Services::Timer::~Timer()
{
}


double Services::Timer::GetElapsed()
{
	return glfwGetTime() - offset;
}


double Services::Timer::Reset()
{
	double previousOffset = offset;
	offset = glfwGetTime();
	return offset - previousOffset;
}

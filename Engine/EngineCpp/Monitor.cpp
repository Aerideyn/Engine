#include "GLFW\glfw3.h"
#include "Monitor.h"

Render::Monitor::~Monitor()
{}

std::vector<Render::Monitor> Render::Monitor::GetMonitorList()
{
	int count;
	GLFWmonitor** list = glfwGetMonitors(&count);
	std::vector<Render::Monitor> returnlist = std::vector<Render::Monitor>();
	for (int i = 0; i < count; i++)
	{
		if (list[i] != nullptr) returnlist.push_back(Render::Monitor(list[i]));
	}
	return returnlist;
}

Render::Monitor Render::Monitor::GetPrimaryMonitor()
{
	return Render::Monitor(glfwGetPrimaryMonitor());
}
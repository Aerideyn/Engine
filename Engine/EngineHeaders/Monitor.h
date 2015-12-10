#pragma once
#include <vector>
struct GLFWmonitor;
namespace Render
{
	class Monitor
	{
		friend class Window;

	public:
		static std::vector<Monitor> GetMonitorList();
		static Monitor GetPrimaryMonitor();
		~Monitor();

	private:
		Monitor(GLFWmonitor* monitor) : Handle(monitor) {};

	public:
		void DoStuff();

	private:
		GLFWmonitor* Handle;

	};
}

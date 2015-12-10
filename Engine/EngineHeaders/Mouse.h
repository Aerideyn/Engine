#pragma once
#include "glm\glm.hpp"

namespace Services
{
	class Mouse
	{
	public:
		Mouse();
		~Mouse();
	public:
		static glm::dvec2 GetMousePosition();
		static void SetMousePosition(double X, double Y);
		static bool LeftMouseButtonDown();
		static bool RightMouseButtonDown();
	};
}

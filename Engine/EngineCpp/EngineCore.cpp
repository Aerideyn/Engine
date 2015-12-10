#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include "EngineCore.h"
#include "Timer.h"
#include "TextureLoader.h"
#include "ShaderLoader.h"
#include <iostream>


/*	todo.

	input:
	joystick support.
	finish mapping keyboard keys to glfw.
	mouse button presses.

	textureing:
	texture filtering / wrapping settings.
	jpg loading.

	window:
	window clear colour.
	window resizing, positioning.
	window resolution.
	
	geometry:
	bounding frustum.
	bounding box
	intersections between bounding volumes.
	
	physics:

*/

EngineCore::EngineCore()
{
	
}

EngineCore::~EngineCore()
{
}

int EngineCore::Initialize()
{
	std::cout << "init glfw" << std::endl;
	if (!glfwInit()) exit(EXIT_FAILURE);
	return 0;
}

void EngineCore::ShutDown()
{
	glfwTerminate();
}

void EngineCore::SetAssetRootPath(const char* Path)
{
	detail::ShaderLoader::SetRootPath(Path);
	detail::TextureLoader::SetRootFilePath(Path);
}

int EngineCore::RunGameLoop(GameLoopCallback UpdateCallback, GameLoopCallback RenderCallback)
{
	Services::Timer clock;
	bool updated = false;

	double t = 0.0;
	double accumulator = 0;
	const double dt = 1.0 / 60.0;
	const int TargetUpdateFrequency = 1000000 / 60;

	while (!gameloopShouldStop)
	{
		double frameTime = clock.Reset();
		if (!gameloopPaused)
		{
			if (frameTime > 0.25) frameTime = 0.25; // note: max frame time to avoid spiral of death
			accumulator += frameTime;

			// if an update is due (or overdue - in which case update until caught up)
			while (accumulator >= dt)
			{
				UpdateCallback(dt);
				t += dt;
				accumulator -= dt;
				updated = true;
			}

			// game is up to date - trigger a render.
			if (updated)
			{
				updated = false;
				// draw the world.
				RenderCallback(dt);
			}
		}
	}
	return 0;
}
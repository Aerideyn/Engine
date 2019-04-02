
#include "EngineCore.h"

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Window\Event.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include "Game.h"

EngineCore* app;

int EngineCore::SetupWindow()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	
	window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(1024, 768), "Window", sf::Style::None, settings));
	window->setMouseCursorVisible(false);
	window->setVerticalSyncEnabled(false);
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	sf::Vector2u Size = window->getSize();
	sf::Mouse::setPosition(sf::Vector2i(Size.x / 2, Size.y / 2), *window);
	
	return 0;
}

int EngineCore::InitializeGLEW()
{
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return 1;
	}
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	return 0;
}

int EngineCore::SetupEngine()
{;
	game = std::shared_ptr<Game>(new Game(window));
	return 0;
}

int EngineCore::RunGameloop()
{
	sf::Clock clock;
	sf::Clock updateTimer;

	bool Paused = false;
	bool updated = false;

	double t = 0.0;
	double accumulator = 0;
	const double dt = 1.0 / 60.0;
	const int TargetUpdateFrequency = 1000000 / 60;

	while (window->isOpen())
	{
		double frameTime = clock.restart().asSeconds();

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window->close();
			}
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Pause)
					Paused = !Paused;
			}
		}	
		if (!Paused)
		{
			if (frameTime > 0.25) frameTime = 0.25; // note: max frame time to avoid spiral of death
			accumulator += frameTime;

			// if an update is due (or overdue - in which case update until caught up)
			while (accumulator >= dt)
			{
				game->Update(dt);
				t += dt;

				accumulator -= dt;
				updated = true;
			}

			if (updated)
			{
				updated = false;
				// Clear the screen
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// draw the world.
				game->Draw(frameTime);

				// render to screen.
				window->display();
			}
		}
	}
	return 0;
}

void EngineCore::BeginGameLoop()
{
	app->RunGameloop();
}

int EngineCore::InitializeEngine()
{
	app = new EngineCore();
	int code = 0;

	code = app->SetupWindow();
	if (code != 0) return code;

	code = app->InitializeGLEW();
	if (code != 0) return code;

	code = app->SetupEngine();
	if (code != 0) return code;

	return 0;
}

void EngineCore::ShutDownEngine()
{

}

EngineCore::~EngineCore()
{
	delete app;
}
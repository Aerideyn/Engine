#pragma once
#include <memory>

namespace sf { class RenderWindow; }
class Game;


class EngineCore
{
private:
	std::shared_ptr<Game> game;
	std::shared_ptr<sf::RenderWindow> window;

	int InitializeGLEW();
	int SetupWindow();
	int SetupEngine();
	int RunGameloop();

	EngineCore(){};

public:
	static int InitializeEngine();
	static void BeginGameLoop();
	static void ShutDownEngine();
	~EngineCore();

};
#pragma once
#include <glm\glm.hpp>
#include <memory>
namespace sf { class RenderWindow; }

class WindowManager
{
	friend class Game;
private:
	static std::shared_ptr<sf::RenderWindow> WindowManager::ptr_GameWindow;

	WindowManager(std::shared_ptr<sf::RenderWindow> window);
	WindowManager(WindowManager const&);
	void operator=(WindowManager const&);

public:
	static glm::ivec2 GetWindowPosition();
	static glm::ivec2 GetWindowSize();
	static float GetAspectRatio();	

	~WindowManager();
};


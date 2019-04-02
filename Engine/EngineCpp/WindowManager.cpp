#include "WindowManager.h"
#include <SFML\Graphics\RenderWindow.hpp>

std::shared_ptr<sf::RenderWindow> WindowManager::ptr_GameWindow;

WindowManager::WindowManager(std::shared_ptr<sf::RenderWindow> window)
{
	ptr_GameWindow = window;
}

WindowManager::~WindowManager()
{

}

glm::ivec2 WindowManager::GetWindowPosition()
{
	sf::Vector2i p = ptr_GameWindow->getPosition();
	return glm::ivec2(p.x, p.y);
}

glm::ivec2 WindowManager::GetWindowSize()
{
	sf::Vector2u size = ptr_GameWindow->getSize();
	return glm::ivec2(size.x, size.y);
}

float WindowManager::GetAspectRatio()
{
	sf::Vector2u size = ptr_GameWindow->getSize();
	return static_cast<float>(size.x) / static_cast<float>(size.y);
}
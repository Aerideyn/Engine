#include "InputService.h"
#include "Game.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Window\Keyboard.hpp>

std::shared_ptr<sf::RenderWindow> InputService::ptr_GameWindow;

InputService::InputService(std::shared_ptr<sf::RenderWindow> gameWindow)
{
	ptr_GameWindow = gameWindow;
}

InputService::~InputService()
{

}

void InputService::SetMousePosition(glm::ivec2 Position)
{
	sf::Mouse::setPosition(sf::Vector2i(Position.x, Position.y), *ptr_GameWindow);
}

glm::ivec2 InputService::GetMousePosition()
{
	sf::Vector2i Position = sf::Mouse::getPosition(*ptr_GameWindow);
	return glm::ivec2(Position.x, Position.y);
}

bool InputService::IsKeyPressed(InputServiceKey::Key keyToCheck)
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyToCheck));
}
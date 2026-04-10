#pragma once
#include <SFML/Graphics.hpp>

class InputField {
private:
	std::string value;
	sf::Text enteredText;
	sf::Font font;
	sf::RectangleShape shape;

	bool isActive;
	bool isCursorVisible;

	sf::Clock cursorClock;
public:
	InputField(sf::Vector2f size, sf::Vector2f coords);
	
	std::string getString();

	void handleEvent(const sf::Event& event);
	void update(sf::Vector2u windowSize);
	void render(sf::RenderWindow& window);
};
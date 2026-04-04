#include "Button.h"


Button::Button(sf::Vector2f size, sf::Vector2f coords, std::string text){
	shape.setPosition(coords);
	shape.setSize(size);

	content.setPosition(coords);
	content.setString(text);
	content.setColor(sf::Color::Red);
	sf::Font font;
	font.loadFromFile("assets/pixel-font.otf");
	content.setFont(font);
}

void Button::render(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(content);
}
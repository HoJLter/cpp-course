#include "Button.h"
#include <iostream>

Button::Button(sf::Vector2f size, sf::Vector2f coords, std::string text){
	shape.setPosition(coords);
	shape.setSize(size);

	label.setString(text);
	label.setColor(sf::Color::Red);
	if (font.loadFromFile("assets/pixel-font.otf")) {
		label.setFont(font);
	}
	else {
		std::cout << "ERROR LOADING FONT";
	}
	sf::FloatRect bounds = label.getGlobalBounds();
	label.setOrigin({ bounds.width / 2, bounds.height / 2 });
	label.setPosition({coords.x+size.x/2, coords.y+size.y/2});
}

void Button::render(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(label);
}
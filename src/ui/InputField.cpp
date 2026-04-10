#include "ui/InputField.h"
#include <iostream>

InputField::InputField(sf::Vector2f size, sf::Vector2f coords) {
	if (!font.loadFromFile("assets/pixel-font.otf")) {
		throw std::runtime_error("[ERROR] Font loading was failed");
	}
	isActive = false;
	isCursorVisible = false;

	shape.setOrigin({ size.x / 2, size.y / 2 });
	shape.setPosition(coords);

	enteredText.setFont(font);
	enteredText.setOrigin({ 0.f, size.y / 2});
	enteredText.setPosition({coords.x+20, coords.y});
	enteredText.setCharacterSize(14);
	enteredText.setString("Enter something");
};

void InputField::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f clickCoords = { event.mouseButton.x, event.mouseButton.y };
		if (shape.getGlobalBounds().contains(clickCoords)) {
			isActive = true;
		}
		else {
			isActive = false;
		}
	}
	if (isActive && event.type == sf::Event::TextEntered) {
		unsigned int unicode = event.text.unicode;
		if (unicode >= '0' && unicode <= '9'){
			value += static_cast<char>(event.text.unicode);
			std::cout << value;
		}
	}
};


void InputField::update(sf::Vector2u windowSize) {
	if (cursorClock.getElapsedTime().asSeconds() >= 0.5f) {
		isCursorVisible = !isCursorVisible;
		cursorClock.restart();
	}

	if (isActive && isCursorVisible) {
		enteredText.setString(value + '|');
	}
	else {
		enteredText.setString(value);
	}
};


void InputField::render(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(enteredText);
};

std::string InputField::getString() {
	return enteredText.getString();
}
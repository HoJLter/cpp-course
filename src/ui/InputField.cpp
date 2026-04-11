#include "ui/InputField.h"
#include "utils/Logger.h"
#include <iostream>

InputField::InputField(sf::Vector2f size, sf::Vector2f coords) {
	if (!font.loadFromFile("assets/pixel-font.otf")) {
		Log::error("Font loading was failed");
		throw std::runtime_error("Font loading was failed");
	}
	isActive = false;
	isCursorVisible = false;

	shape.setOrigin({ size.x / 2.f, size.y / 2.f });
	shape.setPosition(coords);

	enteredText.setFont(font);
	enteredText.setOrigin({ 0.f, size.y / 2.f});
	enteredText.setPosition({coords.x+20, coords.y});
	enteredText.setCharacterSize(14);
	enteredText.setString("Enter something");
	Log::debug("Input field was created");
};

void InputField::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f clickCoords = { 
			static_cast<float>(event.mouseButton.x), 
			static_cast<float>(event.mouseButton.y)
		};
		if (shape.getGlobalBounds().contains(clickCoords)) {
			isActive = true;
			Log::debug("Input field has been activated");
		}
		else {
			isActive = false;
			Log::debug("Input field has been deactivated");
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


void InputField::update() {
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
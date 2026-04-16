#include "ui/InputField.h"
#include "utils/Logger.h"
#include <iostream>

InputField::InputField(sf::Vector2f padding, sf::Vector2f coords, std::function<void()> callback):
	action(callback)
{
	if (!font.loadFromFile("assets/pixel-font.otf")) {
		Log::error("Font loading was failed");
		throw std::runtime_error("Font loading was failed");
	}
	isActive = false;
	isAlarmState = false;
	isCursorVisible = false;

	enteredText.setFont(font);
	enteredText.setCharacterSize(16);
	enteredText.setString("Enter something");
	enteredText.setColor(sf::Color::Black);
	sf::FloatRect textBounds = enteredText.getGlobalBounds();
	sf::Vector2f shapeSize = { textBounds.width + padding.x, textBounds.height + padding.y };

	enteredText.setOrigin({ 0.f, (enteredText.getGlobalBounds().height / 2.f) - 10.f});
	enteredText.setPosition({ coords.x - (shapeSize.x / 2.f) + 10.f, coords.y });
	


	shape.setPosition(coords);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(2);
	shape.setSize(shapeSize);
	shape.setOrigin({ shapeSize.x / 2.f, shapeSize.y / 2.f });

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
		else if (isActive) {
			isActive = false;
			Log::debug("Input field has been deactivated");
		}
	}
	if (isActive && event.type == sf::Event::TextEntered) {
		unsigned int unicode = event.text.unicode;
		if (unicode >= '0' && unicode <= '9') {
			value += static_cast<char>(event.text.unicode);
		}
	}
	if (isActive && event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Enter){
			action();
		}
		if (!value.empty() && event.key.code == sf::Keyboard::Backspace) {
			value.pop_back();
		}
	}
};

void InputField::alarm() {
	Log::warn("Wrong value was entered");
	isAlarmState = true;
	enteredText.setString("WRONG VALUE");
	alarmClock.restart();

}

void InputField::update(sf::RenderWindow& window) {
	if (isAlarmState && alarmClock.getElapsedTime().asSeconds() >= 1.f) {
		isAlarmState = false;
	}

	if (cursorClock.getElapsedTime().asSeconds() >= 0.8f) {
		isCursorVisible = !isCursorVisible;
		cursorClock.restart();
	}

	if (isAlarmState) {
		enteredText.setString("WRONG VALUE");
		return;
	}


	if (isActive && isCursorVisible) {
		enteredText.setString(value + '|');
	}
	else {
		if (!isActive && value.empty()) {
			enteredText.setString("Enter something");
		}
		else {
			enteredText.setString(value);
		}
	}
};


void InputField::render(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(enteredText);
};

std::string InputField::getValue() {
	if (!value.empty()) {
		return value;
	}
	Log::warn("Input field is empty");
	return "0";
}
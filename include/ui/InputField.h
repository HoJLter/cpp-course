#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class InputField {
private:
	std::string value;
	sf::Text enteredText;
	sf::Font font;
	sf::RectangleShape shape;
	std::function<void()> action;

	bool isActive;
	bool isCursorVisible;
	bool isAlarmState;

	sf::Clock cursorClock;
	sf::Clock alarmClock;
public:
	InputField(sf::Vector2f size, sf::Vector2f coords, std::function<void()> callback);
	
	std::string getValue();
	void alarm();

	void handleEvent(const sf::Event& event);
	void update();
	void render(sf::RenderWindow& window);
};
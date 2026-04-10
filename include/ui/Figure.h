#pragma once
#include <SFML/Graphics.hpp>

class Figure {
private:
	sf::ConvexShape shape;
	float speed = 1.f;

public:
	Figure();

	void handleEvent(sf::Event event);
	void update();
	void render(sf::RenderWindow& window);
};
#pragma once
#include <SFML/Graphics.hpp>

class Application {
private:
	sf::RenderWindow window;
	sf::Vector2i windowSize;
public:
	Application(sf::Vector2i windowSize);
	Application();

	int run();
private:
	int processEvents();
	int update();
	int render();
};
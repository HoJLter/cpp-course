#pragma once
#include <SFML/Graphics.hpp>
#include "Figure.h"
#include <cstdint>

class Application {
private:
	sf::RenderWindow window;
	uint16_t width;
	uint16_t height;
	Figure figure;
	
public:
	Application(uint16_t width, uint16_t height);
	Application();

	void run();
private:
	void processEvents();
	void update();
	void render();
};
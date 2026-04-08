#pragma once
#include <SFML/Graphics.hpp>
#include "Figure.h"
#include "Button.h"
#include <cstdint>

class Application {
private:
	sf::RenderWindow window;

	Figure figure;
	Button start;

	sf::View mainView;
	sf::View uiView;
	
	
public:
	Application(uint16_t width, uint16_t height);

	void run();
private:
	void processEvents();
	void update();
	void render();
};
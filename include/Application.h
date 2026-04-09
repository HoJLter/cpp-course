#pragma once
#include <SFML/Graphics.hpp>
#include "Figure.h"
#include "Button.h"
#include "Label.h"
#include <cstdint>

enum class AppState {
	Base,
	DotsCountInput,
	DotsPosInput,
	Result
};

class Application {
private:
	sf::RenderWindow window;
	AppState appState;

	Figure figure;
	Label start_label;
	Button start;

	sf::View mainView;
	sf::View uiView;


public:
	Application(uint16_t width, uint16_t height);

	void run();
	void enterState(AppState state);
private:
	void processEvents();
	void update();
	void render();
};

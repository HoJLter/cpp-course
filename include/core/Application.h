#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include "Scenes.h"


class Application {
private:
	sf::RenderWindow window;
	std::unique_ptr<Scene> curScene;

public:
	Application(uint16_t width, uint16_t height);

	void run();
	void switchScene(std::unique_ptr<Scene> scene);
private:
	void processEvents();
	void update();
	void render();
};

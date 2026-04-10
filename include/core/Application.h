#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include "core/SceneManager.h"
#include "Scenes.h"


class Application {
private:
	sf::RenderWindow window;
	SceneManager sceneManager;
	
public:
	Application(uint16_t width, uint16_t height);

	void run();
private:
	void processEvents();
	void update();
	void render();
};

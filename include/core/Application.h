#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include "core/SceneManager.h"
#include "Scenes.h"


class Application {
private:
	sf::RenderWindow window;
	

public:
	Application(uint16_t width, uint16_t height);

	void run();
private:
	void switchScene(SceneID id);
	void processEvents();
	void update();
	void render();
};

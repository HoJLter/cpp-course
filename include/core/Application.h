#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include "core/SceneSwitcher.h"
#include "Scenes.h"


class Application {
private:
	sf::RenderWindow window;
	std::unique_ptr<Scene> curScene;

public:
	Application(uint16_t width, uint16_t height);

	void run();
private:
	void switchScene(SceneID id);
	void processEvents();
	void update();
	void render();
};

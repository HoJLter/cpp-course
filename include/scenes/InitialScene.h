#pragma once
#include "Scene.h"
#include "ui/Button.h"
#include "ui/Label.h"

class InitialScene : public Scene {
private:
	Label startLabel;
	Button startButton;

public:
	InitialScene(sf::Vector2u windowSize);

	void handleEvent(const sf::Event& event) override;
	void update(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};


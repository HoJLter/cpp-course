#pragma once
#include "scenes/Scene.h"
#include "ui/Button.h"
#include "ui/Label.h"

class TestsScene : public Scene {
private:
	Button returnToInitial;
	sf::VertexArray lines;
	
public:
	TestsScene(sf::Vector2u windowSize, ISceneSwitcher& sceneSwitcher);

	void handleEvent(const sf::Event& event) override;
	void update(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};


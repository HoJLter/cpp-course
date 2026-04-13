#pragma once
#include "scenes/Scene.h"
#include "ui/Label.h"
#include "ui/InputField.h"


class DotInputScene : public Scene {
private:
	Label dotLabel;
	int dotCountRemaining;
	sf::VertexArray dots;
	sf::ConvexShape contour;

	Label errorLabel;
	bool isRestarting;
	sf::Clock restartClock;

	bool isTransfering;
	sf::Clock transferClock;

public:
	DotInputScene(sf::Vector2u windowSize, ISceneSwitcher& sceneSwitcher);

	void addDot(sf::Vector2f dot);
	void handleEvent(const sf::Event& event) override;
	void update(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};

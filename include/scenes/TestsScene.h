#pragma once
#include "scenes/Scene.h"
#include "ui/Button.h"
#include "ui/Label.h"


sf::ConvexShape makeConvex(const std::vector<sf::Vector2f>& pts, sf::Color color);


class TestsScene : public Scene {
private:
	Button calculate;
	Button returnToInitial;
	sf::VertexArray lines;

	struct figure {
		sf::ConvexShape contour;
		sf::VertexArray diagonals;
		float diaLen;
	};
	std::vector<figure> testFigures;

	bool isCalcButtonPressed;
	bool isCalcEnded;

	sf::Clock cooldown;
	
public:
	TestsScene(sf::Vector2u windowSize, ISceneSwitcher& sceneSwitcher);

	void handleEvent(const sf::Event& event) override;
	void update(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};


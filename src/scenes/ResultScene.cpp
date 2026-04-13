#include "scenes/ResultScene.h"
#include "utils/Log.h"

ResultScene::ResultScene(sf::Vector2u windowSize, ISceneSwitcher& ss) :
	Scene(ss),
	contour(ss.shared.contour),
	dots(ss.shared.dots)
{

	dots.setPrimitiveType(sf::LineStrip);
	contour.setFillColor(sf::Color::Transparent);
	contour.setOutlineThickness(3);
	contour.setOutlineColor(sf::Color::White);
	Log::debug("ResultScene created");
}

void ResultScene::handleEvent(const sf::Event& event) {
}

void ResultScene::update(sf::RenderWindow& window) {
}

void ResultScene::render(sf::RenderWindow& window) {
	window.draw(contour);
}
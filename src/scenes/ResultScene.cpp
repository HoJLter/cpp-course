#include "scenes/ResultScene.h"
#include "utils/Log.h"

ResultScene::ResultScene(sf::Vector2u windowSize, ISceneSwitcher& ss) :
	Scene(ss),
	contour(ss.shared.contour),
	dots(ss.shared.dots),
	calculate({ 50.f, 20.f }, 
		{ static_cast<float>(windowSize.x) / 2.f, windowSize.y - 150.f }, 
		"Calculate",
		[this]() {
			
		})
{

	dots.setPrimitiveType(sf::LineStrip);
	contour.setFillColor(sf::Color::Transparent);
	contour.setOutlineThickness(3);
	contour.setOutlineColor(sf::Color::White);
	Log::debug("ResultScene created");
}

void ResultScene::handleEvent(const sf::Event& event){
	calculate.handleEvent(event);
}

void ResultScene::update(sf::RenderWindow& window) {
	sf::Vector2i curPosInt = sf::Mouse::getPosition(window);
	sf::Vector2f curPosFloat(
		static_cast<float>(curPosInt.x),
		static_cast<float>(curPosInt.y)
	);

	calculate.update(curPosFloat);
}

void ResultScene::render(sf::RenderWindow& window) {
	window.draw(contour);
	calculate.render(window);
}
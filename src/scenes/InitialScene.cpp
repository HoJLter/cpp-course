#include "scenes/InitialScene.h"

InitialScene::InitialScene(sf::Vector2u windowSize) :
	startLabel("Enter count of dots.",
		{ static_cast<float>(windowSize.x) / 2, windowSize.y - 150.f },
		18),
	startButton({ 50, 20 }, { static_cast<float>(windowSize.x) / 2, windowSize.y - 50.f }, "START",
		[this]() {
			this->startLabel.switchVisibility();
		}) {
}

void InitialScene::handleEvent(const sf::Event& event) {
	startButton.handleEvent(event);
}

void InitialScene::update(sf::RenderWindow& window) {
	sf::Vector2i curPosInt = sf::Mouse::getPosition(window);
	sf::Vector2f curPosFloat(
		static_cast<float>(curPosInt.x),
		static_cast<float>(curPosInt.y)
	);

	startButton.update(curPosFloat);
}

void InitialScene::render(sf::RenderWindow& window) {
	startButton.render(window);
	startLabel.render(window);
}
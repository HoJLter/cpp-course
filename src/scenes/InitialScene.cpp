#include "scenes/InitialScene.h"
#include <iostream>

InitialScene::InitialScene(sf::Vector2u windowSize, ISceneSwitcher& ss): 
	Scene(ss),
	startLabel("Enter count of dots.",
		{ static_cast<float>(windowSize.x) / 2.f, windowSize.y - 150.f },
		18),
	startButton({ 50.f, 20.f }, { static_cast<float>(windowSize.x) / 2.f, windowSize.y - 50.f }, "START",
		[this]() {
			sceneSwitcher.requestSwitchScene(SceneID::DotCountInput);
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
#include "scenes/InitialScene.h"
#include <iostream>
#include "utils/Log.h"

InitialScene::InitialScene(sf::Vector2u windowSize, ISceneSwitcher& ss): 
	Scene(ss),
	startLabel("Welcome to dia calculator",
		{ static_cast<float>(windowSize.x) / 2.f, windowSize.y - 600.f },
		18),
	testButton({ 50.f, 20.f }, { static_cast<float>(windowSize.x) / 2.f, windowSize.y - 250.f }, "TESTS",
		[this]() {
			sceneSwitcher.requestSwitchScene(SceneID::Tests);
		}),
	startButton({ 50.f, 20.f }, { static_cast<float>(windowSize.x) / 2.f, windowSize.y - 150.f }, "START",
		[this]() {
			sceneSwitcher.requestSwitchScene(SceneID::DotCountInput);
		}) {
	Log::debug("Initial scene created");
}

void InitialScene::handleEvent(const sf::Event& event) {
	startButton.handleEvent(event);
	testButton.handleEvent(event);
}

void InitialScene::update(sf::RenderWindow& window) {
	sf::Vector2i curPosInt = sf::Mouse::getPosition(window);
	sf::Vector2f curPosFloat(
		static_cast<float>(curPosInt.x),
		static_cast<float>(curPosInt.y)
	);

	startButton.update(curPosFloat);
	testButton.update(curPosFloat);
}

void InitialScene::render(sf::RenderWindow& window) {
	startButton.render(window);
	testButton.render(window);
	startLabel.render(window);
}
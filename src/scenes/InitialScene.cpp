#include "scenes/InitialScene.h"
#include <iostream>
#include "utils/Log.h"

InitialScene::InitialScene(sf::Vector2u windowSize, ISceneSwitcher& ss): 
	Scene(ss),
	startLabel("Welcome to dia calculator",
		{ static_cast<float>(windowSize.x) / 2.f, windowSize.y - 600.f },
		18),
	startButton({ 50.f, 20.f }, { static_cast<float>(windowSize.x) / 2.f, windowSize.y - 150.f }, "START",
		[this]() {
			sceneSwitcher.requestSwitchScene(SceneID::DotCountInput);
		}) {
	Log::debug("Initial scene created");
}

void InitialScene::handleEvent(const sf::Event& event) {
	startButton.handleEvent(event);
}

void InitialScene::update(sf::RenderWindow& window) {
	startButton.update(window);
}

void InitialScene::render(sf::RenderWindow& window) {
	startButton.render(window);
	startLabel.render(window);
}
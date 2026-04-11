#include "scenes/DotCountInputScene.h"

DotCountInputScene::DotCountInputScene(sf::Vector2u windowSize, ISceneSwitcher& ss) :
	Scene(ss),
	dotCountInput({300.f, 50.f}, {windowSize.x / 2.f, windowSize.y - 200.f}),
	dotInputLabel("Enter count of dots:", { windowSize.x / 2.f, windowSize.y - 100.f}, 14){	
}


void DotCountInputScene::handleEvent(const sf::Event& event) {
	dotCountInput.handleEvent(event);
}

void DotCountInputScene::update(sf::RenderWindow& window) {
	dotCountInput.update();
}

void DotCountInputScene::render(sf::RenderWindow& window) {
	dotCountInput.render(window);
	dotInputLabel.render(window);
}
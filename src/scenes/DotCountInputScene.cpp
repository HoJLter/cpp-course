#include "scenes/DotCountInputScene.h"
#include "utils/Log.h"

DotCountInputScene::DotCountInputScene(sf::Vector2u windowSize, ISceneSwitcher& ss) :
	Scene(ss),
	dotCountInput({100.f, 50.f}, 
		{windowSize.x / 2.f, windowSize.y - 100.f},
		[this]() {
			int value = std::stoi(this->dotCountInput.getValue());
			Log::debug("Input callback called with value: " + std::to_string(value));
			if (value == 0 || value > 20) {
				this->dotCountInput.alarm();
			}
			else {
				sceneSwitcher.shared.dotCount = value;
				sceneSwitcher.requestSwitchScene(SceneID::DotInput);
			}
			
		}),
	dotInputLabel("Enter count of dots:", { windowSize.x / 2.f, windowSize.y - 200.f}, 18){	
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
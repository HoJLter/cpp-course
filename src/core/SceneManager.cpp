#include <memory>
#include "core/SceneManager.h"


SceneManager::SceneManager(sf::RenderWindow& window): window(window) {
	curScene = std::make_unique<InitialScene>(window.getSize(), *this);
}

void SceneManager::requestSwitchScene(SceneID id) {
	requestedScene = id;
}

void SceneManager::switchScene() {
	if (requestedScene.has_value()) {
		switch (requestedScene.value()) {
		case SceneID::Initial: {
			curScene = std::make_unique<InitialScene>(window.getSize(), *this);
			break;
		}
		case SceneID::DotCountInput: {
			curScene = std::make_unique<DotCountInputScene>(window.getSize(), *this);
			break;
		}
		case SceneID::DotInput: {
			curScene = std::make_unique<InitialScene>(window.getSize(), *this);
			break;
		}
		case SceneID::Result: {
			curScene = std::make_unique<InitialScene>(window.getSize(), *this);
			break;
		}
		}
	}
}

void SceneManager::handleEvent(const sf::Event& event) {
	curScene->handleEvent(event);
	switchScene();
}

void SceneManager::update() {
	curScene->update(window);
	switchScene();
}

void SceneManager::render() {
	curScene->render(window);
}
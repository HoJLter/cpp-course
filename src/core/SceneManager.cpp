#include <memory>
#include "core/SceneManager.h"


SceneManager::SceneManager(sf::RenderWindow& w): window(w) {
}

void SceneManager::requestSwitchScene(SceneID id) {
	requestedScene = id;
}

void SceneManager::switchScene() {
	if (requestedScene.has_value()) {
		SceneID id = requestedScene.value();
		switch (id) {
		case SceneID::Initital: {
			curScene = std::make_unique<InitialScene>(window.getSize());
		}
		case SceneID::DotCountInput: {
			curScene = std::make_unique<DotCountInputScene>(window.getSize());
		}
		case SceneID::DotInput: {
			curScene = std::make_unique<InitialScene>(window.getSize());
		}
		case SceneID::Result: {
			curScene = std::make_unique<InitialScene>(window.getSize());
		}
		}
	}
}

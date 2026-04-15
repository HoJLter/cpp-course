#include <memory>
#include "core/SceneManager.h"
#include "utils/Log.h"

std::string sceneIdToStr(SceneID id) {
	switch (id) {
	case SceneID::Initial:  return "InitialScene";
	case SceneID::DotCountInput: return "DotCountInputScene";
	case SceneID::DotInput: return "DotInputScene";
	case SceneID::Result: return "ResultScene";
	case SceneID::Tests: return "TestsScene";
	default: return "UnknownScene";
	}
}

SceneManager::SceneManager(sf::RenderWindow& window): window(window) {
	curScene = std::make_unique<InitialScene>(window.getSize(), *this);
}

void SceneManager::requestSwitchScene(SceneID id) {
	Log::debug("New scene switch request: " + sceneIdToStr(id));
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
			curScene = std::make_unique<DotInputScene>(window.getSize(), *this);
			break;
		}
		case SceneID::Result: {
			curScene = std::make_unique<ResultScene>(window.getSize(), *this);
			break;
		}
		case SceneID::Tests: {
			curScene = std::make_unique<TestsScene>(window.getSize(), *this);
			break;
		}
		}
		Log::debug("Scene has been switched to " + sceneIdToStr(requestedScene.value()));
		requestedScene.reset();
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
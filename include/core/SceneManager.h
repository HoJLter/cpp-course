#pragma once
#include "Scenes.h"
#include <memory>
#include <optional>


enum class SceneID {
	Initital,
	DotCountInput,
	DotInput,
	Result
};

class SceneManager {
private:
	sf::RenderWindow& window;
	std::unique_ptr<Scene> curScene;
	std::optional<SceneID> requestedScene;
public:
	SceneManager(sf::RenderWindow& window);

	void requestSwitchScene(SceneID id);
	void switchScene();

	void handleEvent();
	void update();
	void render();
};

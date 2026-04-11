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

class SceneManager: public ISceneSwitcher {
private:
	sf::RenderWindow& window;
	std::unique_ptr<Scene> curScene;
	std::optional<SceneID> requestedScene;
public:
	SceneManager(sf::RenderWindow& window);

	void requestSwitchScene(SceneID id) override;
	void switchScene();

	void handleEvent(const sf::Event& event);
	void update();
	void render();
};


class ISceneSwitcher {
private:
	std::optional<SceneID> requestedScene;
public:
	virtual void requestSwitchScene(SceneID id) = 0;
};
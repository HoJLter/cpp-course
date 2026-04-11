#pragma once
#include "Scene.h"
#include "ui/Label.h"
#include "ui/InputField.h"


class DotCountInputScene : public Scene {
private:
	InputField dotCountInput;
	Label dotInputLabel;

public:
	DotCountInputScene(sf::Vector2u windowSize, ISceneSwitcher& sceneSwitcher);

	void handleEvent(const sf::Event& event) override;
	void update(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};


#pragma once
#include "SFML/Graphics.hpp"

class UI {
public:
	virtual void handleEvent(const sf::Event& event);
	virtual void update(const sf::RenderWindow& window);
	virtual void render(const sf::RenderWindow& window);
};
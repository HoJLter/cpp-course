#pragma once
#include "SFML/Graphics.hpp"
#include "ui/UI.h"

class Label : public UI {
private:
	sf::Text content;
	sf::Vector2f coords;
	sf::Font font;

	bool isVisible;

public:
	Label(std::string str, sf::Vector2f coords, uint16_t charSize);
	void setString(const std::string& str);

	void switchVisibility();

	void handleEvent(const sf::Event& event) override;
	void update(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};

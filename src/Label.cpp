#include "Label.h"


Label::Label(std::string str, sf::Vector2f coords, uint16_t charSize) {
	if (!font.loadFromFile("assets/pixel-font.otf")) {
		throw std::runtime_error("[ERROR] Font loading was failed.");
	}
	content.setFont(font);
	content.setString(str);
	content.setCharacterSize(charSize);
	sf::FloatRect bounds = content.getGlobalBounds();

	content.setOrigin({bounds.width/2, bounds.height/2});

	content.setPosition(coords);
}

void Label::switchVisibility() {
	isVisible = !isVisible;
}

void Label::render(sf::RenderWindow& window, sf::View uiView) {
	if (isVisible) {
		sf::View curView = window.getView();
		window.setView(uiView);
		window.draw(content);
		window.setView(curView);
	}
}

#include "scenes/DotInputScene.h"
#include "utils/Log.h"


void DotInputScene::addDot(sf::Vector2f dot) {
	if (dotCountRemaining > 0) {
		dots.append(dot);
		dotCountRemaining--;
	}
	if (dotCountRemaining == 0) {
		for (int i = 0; i < sceneSwitcher.shared.getDotCount(); i++) {
			contour.setPoint(i, dots[i].position);
		}
	}
}

DotInputScene::DotInputScene(sf::Vector2u windowSize, ISceneSwitcher& ss) :
	Scene(ss),
	dotCountRemaining(ss.shared.getDotCount()),
	contour(ss.shared.getDotCount()),
	dotLabel("20 dots remains",
		{ windowSize.x / 2.f, windowSize.y - 100.f },
		18)
{
	dots.setPrimitiveType(sf::LineStrip);
	contour.setFillColor(sf::Color::Transparent);
	contour.setOutlineThickness(3);
	contour.setOutlineColor(sf::Color::White);
	Log::debug("DotInputScene created");
}

void DotInputScene::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed && dotCountRemaining != 0) {
		sf::Vector2f mousePos = {
			static_cast<float>(event.mouseButton.x),
			static_cast<float>(event.mouseButton.y)
		};
		Log::debug("Dot x:" + std::to_string((int)mousePos.x)+ 
			" y: " + std::to_string((int)mousePos.y));
		addDot(mousePos);
	}
}

void DotInputScene::update(sf::RenderWindow& window) {
	dotLabel.setString(std::to_string(dotCountRemaining) + " dots remains");
}

void DotInputScene::render(sf::RenderWindow& window) {
	dotLabel.render(window);
	if (dotCountRemaining != 0) {
		window.draw(dots);
	}
	else {
		window.draw(contour);
	}
}
#include "scenes/DotInputScene.h"
#include "utils/Log.h"
#include "core/Algorithms.h"


void DotInputScene::addDot(sf::Vector2f dot) {
	if (dotCountRemaining > 0) {
		dots.append(dot);
		dotCountRemaining--;
	}
	if (dotCountRemaining == 0) {
		for (int i = 0; i < sceneSwitcher.shared.dotCount; i++) {
			contour.setPoint(i, dots[i].position);
		}
		if (isConvex(dots, sceneSwitcher.shared.dotCount)) {
			contour.setOutlineColor(sf::Color::Green);
			sceneSwitcher.shared.dots = dots;
			sceneSwitcher.shared.contour = contour;

			isTransfering = true;
			transferClock.restart();
		}
		else {
			restartClock.restart();
			isRestarting = true;
			contour.setOutlineColor(sf::Color::Red);
			
		}
		Log::debug("Is convex? " + 
			std::to_string(isConvex(dots, sceneSwitcher.shared.dotCount)));
	}
}

DotInputScene::DotInputScene(sf::Vector2u windowSize, ISceneSwitcher& ss) :
	Scene(ss),
	dotCountRemaining(ss.shared.dotCount),
	contour(ss.shared.dotCount),
	dotLabel("20 dots remains",
		{ windowSize.x / 2.f, windowSize.y - 100.f },
		18),
	errorLabel("Shape is'nt convex!", 
		{windowSize.x/2.f, 100.f},
		16)
{
	isRestarting = false;

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

	if (isRestarting && restartClock.getElapsedTime().asSeconds() > 3.f) {
		Log::debug("Restarting dot input");
		isRestarting = false;
		dotCountRemaining = sceneSwitcher.shared.dotCount;
		dots.clear();
	}

	if (isTransfering && transferClock.getElapsedTime().asSeconds() > 3.f) {
		isTransfering = false;
		sceneSwitcher.requestSwitchScene(SceneID::Result);
	}
}

void DotInputScene::render(sf::RenderWindow& window) {
	dotLabel.render(window);
	if (dotCountRemaining != 0) {
		window.draw(dots);
	}
	else {
		window.draw(contour);
	}
	if (isRestarting) {
		errorLabel.render(window);
	}
}
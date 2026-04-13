#include "scenes/ResultScene.h"
#include "core/Algorithms.h"
#include "utils/Log.h"

ResultScene::ResultScene(sf::Vector2u windowSize, ISceneSwitcher& ss) :
	Scene(ss),
	contour(ss.shared.contour),
	dots(ss.shared.dots),
	calculate({ 50.f, 20.f }, 
		{ static_cast<float>(windowSize.x) / 2.f, windowSize.y - 150.f }, 
		"Calculate",
		[this]() {
			isCalcButtonPressed = true;
			calcLossLenDia(dots, diaArr, lenSum);
			isCalcEnded = true;
			cooldown.restart();

		}),
	returnToInitial({ 50.f, 20.f },
		{ static_cast<float>(windowSize.x) / 2.f, windowSize.y - 150.f },
		"Continue",
		[this]() {
			if (cooldown.getElapsedTime().asSeconds() > 0.5f) {
				sceneSwitcher.requestSwitchScene(SceneID::Initial);
			}
		})
{
	lenSum = 0;
	isCalcButtonPressed = false;
	isCalcEnded = false;
	diaArr.setPrimitiveType(sf::Lines);

	dots.setPrimitiveType(sf::LineStrip);
	contour.setFillColor(sf::Color::Transparent);
	contour.setOutlineThickness(3);
	contour.setOutlineColor(sf::Color::White);
	Log::debug("ResultScene created");
}

void ResultScene::handleEvent(const sf::Event& event){
	if (!isCalcButtonPressed) {
		calculate.handleEvent(event);
	}
	if (isCalcEnded) {
		returnToInitial.handleEvent(event);
	}
}

void ResultScene::update(sf::RenderWindow& window) {
	sf::Vector2i curPosInt = sf::Mouse::getPosition(window);
	sf::Vector2f curPosFloat(
		static_cast<float>(curPosInt.x),
		static_cast<float>(curPosInt.y)
	);
	if (!isCalcButtonPressed) {
		calculate.update(curPosFloat);
	}
	if (isCalcEnded) {
		returnToInitial.update(curPosFloat);
	}
}

void ResultScene::render(sf::RenderWindow& window) {
	window.draw(contour);
	window.draw(diaArr);
	if (!isCalcButtonPressed) {
		calculate.render(window);
	}
	if (isCalcEnded) {
		returnToInitial.render(window);
	}
}

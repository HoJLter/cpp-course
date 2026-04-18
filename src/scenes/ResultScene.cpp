#include "scenes/ResultScene.h"
#include "algo/Triangulators.h"
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
			sf::Clock time;
			std::unique_ptr<ITriangulator> triangulator = std::make_unique<RecursiveTriangulator>();
			TriangulationResult res = triangulator->triangulate(vertexArrToPoly(dots));
			for (const Edge& x : res.diagonals) {
				diaArr.append(dots[x.aID]);
				diaArr.append(dots[x.bID]);
			}
			Log::debug("Time passed: " + std::to_string(time.getElapsedTime().asMicroseconds()));
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
	if (!isCalcButtonPressed) {
		calculate.update(window);
	}
	if (isCalcEnded) {
		returnToInitial.update(window);
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

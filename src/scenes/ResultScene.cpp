#include "scenes/ResultScene.h"
#include "algo/Triangulators.h"
#include "utils/Log.h"


void ResultScene::prevTriangulator() {
	switch (curTriangulator) {
		case TriangulatorType::Ear: {
			curTriangulator = TriangulatorType::Dynamic;
			break;
		}
		case TriangulatorType::Recursive: {
			curTriangulator = TriangulatorType::Ear;
			break;
		}
		case TriangulatorType::Dynamic: {
			curTriangulator = TriangulatorType::Recursive;
			break;
		}
	}
}

void ResultScene::nextTriangulator() {
	switch (curTriangulator) {
		case TriangulatorType::Ear: {
			curTriangulator = TriangulatorType::Recursive;
			break;
		}
		case TriangulatorType::Recursive: {
			curTriangulator = TriangulatorType::Dynamic;
			break;
		}
		case TriangulatorType::Dynamic: {
			curTriangulator = TriangulatorType::Ear;
			break;
		}
	}
}

ResultScene::ResultScene(sf::Vector2u windowSize, ISceneSwitcher& ss) :
	Scene(ss),
	contour(ss.shared.contour),
	dots(ss.shared.dots),
	resultData("Time: 1234 Len: 123.45678",
		{ static_cast<float>(windowSize.x) / 2.f, 100.f },
		18),
	currentTriangulatorLabel("Current triangulator: Ear" ,
		{ static_cast<float>(windowSize.x) / 2.f, windowSize.y - 50.f },
		14),
	calculate({ 50.f, 20.f }, 
		{ static_cast<float>(windowSize.x) / 2.f, windowSize.y - 150.f }, 
		"Calculate",
		[this]() {
			isCalcButtonPressed = true;
			sf::Clock time;
			std::unique_ptr<ITriangulator> triangulator;
			switch (curTriangulator) {
				case TriangulatorType::Ear: {
					triangulator = std::make_unique<EarTriangulator>();
					break;
				}
				case TriangulatorType::Recursive: {
					triangulator = std::make_unique<RecursiveTriangulator>();
					break;
				}
				case TriangulatorType::Dynamic: {
					triangulator = std::make_unique<DynamicTriangulator>();
					break;
				}

								
			}
			TriangulationResult res = triangulator->triangulate(vertexArrToPoly(dots));
			diaArr.clear();
			for (const Edge& x : res.diagonals) {
				diaArr.append(dots[x.aID]);
				diaArr.append(dots[x.bID]);
			}
			resultData.setString("Time: " + 
				std::to_string(time.getElapsedTime().asMicroseconds())
				+ " Len: " + 
				std::to_string(res.diagonalsLen));
			isCalcEnded = true;
			cooldown.restart();
		}),
	nextButton({ 10.f, 10.f },
		{ static_cast<float>(windowSize.x) - 50.f, windowSize.y - 150.f },
		">",
		[this]() {
			nextTriangulator();
			}),
	prevButton({ 10.f, 10.f },
		{50.f, windowSize.y - 150.f },
		"<",
		[this]() {
			prevTriangulator();
		})
{
	lenSum = 0;
	isCalcButtonPressed = false;
	isCalcEnded = false;
	curTriangulator = TriangulatorType::Ear;
	diaArr.setPrimitiveType(sf::Lines);

	dots.setPrimitiveType(sf::LineStrip);
	contour.setFillColor(sf::Color::Transparent);
	contour.setOutlineThickness(3);
	contour.setOutlineColor(sf::Color::White);
	Log::debug("ResultScene created");
}

void ResultScene::handleEvent(const sf::Event& event){
	calculate.handleEvent(event);
	nextButton.handleEvent(event);
	prevButton.handleEvent(event);
	if (isCalcEnded && event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Enter) {
			sceneSwitcher.requestSwitchScene(SceneID::Initial);
		}
	}
}

void ResultScene::update(sf::RenderWindow& window) {
	{
		std::string triangulatorStr;
		switch (curTriangulator) {
			case TriangulatorType::Ear: {
				triangulatorStr = "Ear";
				break;
			}
			case TriangulatorType::Recursive: {
				triangulatorStr = "Recursive";
				break;
			}
			case TriangulatorType::Dynamic: {
				triangulatorStr = "Dynamic";
				break;
			}
		}
		currentTriangulatorLabel.setString("Current triangulator: " + triangulatorStr);
	}
	calculate.update(window);
	nextButton.update(window);
	prevButton.update(window);

}

void ResultScene::render(sf::RenderWindow& window) {
	window.draw(contour);
	window.draw(diaArr);
	calculate.render(window);
	currentTriangulatorLabel.render(window);
	nextButton.render(window);
	prevButton.render(window);
	if (isCalcEnded) {
		resultData.render(window);
	}
}

class Matrix() {
	int rows;
	int cols;


	void print() {
		return rows
	}
}

Matrix a;
a.print();






Matrix a, b;

Matrix c = a.operator+(b);
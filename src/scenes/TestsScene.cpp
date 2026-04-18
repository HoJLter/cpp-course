#include "scenes/TestsScene.h"
#include "algo/Triangulators.h"
#include "utils/Log.h"


sf::ConvexShape makeConvex(const std::vector<sf::Vector2f>& pts, sf::Color color)
{
	sf::ConvexShape shape;
	shape.setPointCount(pts.size());

	for (size_t i = 0; i < pts.size(); ++i)
		shape.setPoint(i, pts[i]);

	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(color);
	shape.setOutlineThickness(2.f);

	return shape;
}


TestsScene::TestsScene(sf::Vector2u windowSize, ISceneSwitcher& ss) :
	Scene(ss),
	calculate({ 50.f, 20.f },
		{ static_cast<float>(windowSize.x) / 2.f, windowSize.y - 150.f },
		"Calculate",
		[this]() {
			isCalcButtonPressed = true;
			for (auto& fig : testFigures) {
				sf::VertexArray dots;
				for (int i = 0; i < fig.contour.getPointCount(); i++) {
					dots.append(sf::Vertex(fig.contour.getTransform().transformPoint(fig.contour.getPoint(i))));
				}

				std::unique_ptr<ITriangulator> triangulator = std::make_unique<RecursiveTriangulator>();
				TriangulationResult res = triangulator->triangulate(vertexArrToPoly(dots));
				for (const Edge& x : res.diagonals) {
					diaArr.append(dots[x.aID]);
					diaArr.append(dots[x.bID]);
				}
			}
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
	for (auto& fig : testFigures) {
		fig.contour.setFillColor(sf::Color::Transparent);
		fig.contour.setOutlineThickness(3);
		fig.contour.setOutlineColor(sf::Color::White);
	}

	isCalcButtonPressed = false;
	isCalcEnded = false;

	Log::debug("TestsScene created");
	diaArr.setPrimitiveType(sf::Lines);

	float width = windowSize.x;
	float height = windowSize.y;

	float x = width / 2.f;
	float y1 = height / 3.f;
	float y2 = 2.f * height / 3.f;

	//вертикаль
	diaArr.append(sf::Vertex{ {x, 0.f}, sf::Color::White });
	diaArr.append(sf::Vertex{ {x, y2}, sf::Color::White });

	//гор1
	diaArr.append(sf::Vertex{ {0.f, y1}, sf::Color::White });
	diaArr.append(sf::Vertex{ {width, y1}, sf::Color::White });
	//гор2
	diaArr.append(sf::Vertex{ {0.f, y2}, sf::Color::White });
	diaArr.append(sf::Vertex{ {width, y2}, sf::Color::White });

	{
		figure fig;
		fig.contour = makeConvex({
			{ 55.f, 120.f },
			{ 95.f, 55.f },
			{ 185.f, 40.f },
			{ 235.f, 100.f },
			{ 165.f, 185.f }
			}, sf::Color::White);
		fig.contour.setPosition({ 0.f, 0.f });
		fig.diagonals.setPrimitiveType(sf::Lines);
		testFigures.push_back(fig);
	}

	{
		figure fig;
		fig.contour = makeConvex({
			{ 35.f, 95.f },
			{ 85.f, 40.f },
			{ 185.f, 25.f },
			{ 250.f, 70.f },
			{ 260.f, 150.f },
			{ 110.f, 210.f }
			}, sf::Color::White);
		fig.contour.setPosition({ width / 2.f, 0.f });
		fig.diagonals.setPrimitiveType(sf::Lines);
		testFigures.push_back(fig);
	}

	{
		figure fig;
		fig.contour = makeConvex({
			{ 30.f, 115.f },
			{ 55.f, 55.f },
			{ 110.f, 28.f },
			{ 185.f, 25.f },
			{ 240.f, 65.f },
			{ 255.f, 125.f },
			{ 225.f, 195.f },
			{ 85.f, 225.f }
			}, sf::Color::White);
		fig.contour.setPosition({ 0.f, height / 3.f });
		fig.diagonals.setPrimitiveType(sf::Lines);
		testFigures.push_back(fig);
	}

	{
		figure fig;
		fig.contour = makeConvex({
			{ 28.f, 125.f },
			{ 40.f, 78.f },
			{ 62.f, 45.f },
			{ 100.f, 24.f },
			{ 145.f, 18.f },
			{ 190.f, 22.f },
			{ 228.f, 38.f },
			{ 255.f, 68.f },
			{ 268.f, 108.f },
			{ 263.f, 150.f },
			{ 240.f, 190.f },
			{ 205.f, 218.f },
			{ 155.f, 232.f },
			{ 105.f, 228.f },
			{ 63.f, 205.f },
			{ 38.f, 170.f }
			}, sf::Color::White);
		fig.contour.setPosition({ width / 2.f, height / 3.f });
		fig.diagonals.setPrimitiveType(sf::Lines);
		testFigures.push_back(fig);
	}

}

void TestsScene::handleEvent(const sf::Event& event) {
	if (!isCalcButtonPressed) {
		calculate.handleEvent(event);
	}
	if (isCalcEnded) {
		returnToInitial.handleEvent(event);
	}
}

void TestsScene::update(sf::RenderWindow& window) {
	if (!isCalcButtonPressed) {
		calculate.update(window);
	}
	if (isCalcEnded) {
		returnToInitial.update(window);
	}

}

void TestsScene::render(sf::RenderWindow& window) {
	for (auto fig : testFigures) {
		window.draw(fig.diagonals);
		window.draw(fig.contour);
	}

	if (!isCalcButtonPressed) {
		calculate.render(window);
	}
	if (isCalcEnded) {
		returnToInitial.render(window);
	}

	window.draw(diaArr);

}
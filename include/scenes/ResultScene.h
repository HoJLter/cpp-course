#include "scenes/Scene.h"
#include "ui/Label.h"
#include "ui/Button.h"
#include "algo/Triangulators.h"



class ResultScene : public Scene {
private:
	float lenSum;

	sf::ConvexShape contour;
	sf::VertexArray dots;

	Button calculate;
	Label currentTriangulatorLabel;
	TriangulatorType curTriangulator;
	Button nextButton;
	Button prevButton;

	sf::VertexArray diaArr;
	Label resultData;

	sf::Clock cooldown;
	bool isCalcButtonPressed;
	bool isCalcEnded;

	void nextTriangulator();
	void prevTriangulator();
public:
	ResultScene(sf::Vector2u windowSize, ISceneSwitcher& sceneSwitcher);

	void handleEvent(const sf::Event& event) override;
	void update(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};

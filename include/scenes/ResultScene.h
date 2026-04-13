#include "scenes/Scene.h"
#include "ui/Button.h"

class ResultScene : public Scene {
private:
	sf::ConvexShape contour;
	sf::VertexArray dots;
	Button calculate;

public:
	ResultScene(sf::Vector2u windowSize, ISceneSwitcher& sceneSwitcher);

	void handleEvent(const sf::Event& event) override;
	void update(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
};

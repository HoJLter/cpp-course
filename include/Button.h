#include "SFML/Graphics.hpp"

class Button {
private:
	sf::RectangleShape shape;
	sf::Text content;

	sf::Vector2f size;
	sf::Vector2f coords;

public:
	Button(sf::Vector2f size, sf::Vector2f coords, std::string text);
	void update();
	void handleEvent(sf::Event event, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
};
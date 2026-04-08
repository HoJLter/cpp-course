#include "SFML/Graphics.hpp"


class Button {
private:
	sf::RectangleShape shape;
	sf::Text label;
	sf::Font font;

	bool isPressed;

public:
	Button(sf::Vector2f size, sf::Vector2f coords, std::string text);
	void update(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void render(sf::RenderWindow& window, sf::View);
};
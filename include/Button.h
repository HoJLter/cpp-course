#include "SFML/Graphics.hpp"

struct ButtonParams {
	bool verticalCenter = false;
};


class Button {
private:
	sf::RectangleShape shape;
	sf::Text label;
	sf::Font font;
	
	ButtonParams params;

	bool isPressed;

public:
	Button(sf::Vector2f size, sf::Vector2f coords, std::string text, const ButtonParams& params чч);
	void update(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void render(sf::RenderWindow& window, sf::View);
};
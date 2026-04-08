#include "Figure.h"
#include <iostream>


Figure::Figure() {
	shape.setPosition(0, 0);
	shape.setFillColor(sf::Color::Red);
	shape.setPointCount(3);

	shape.setPoint(0, { 300, 0 });
	shape.setPoint(1, { 0, 300 });
	shape.setPoint(2, { 300, 300 });

	sf::FloatRect bounds = shape.getLocalBounds();
	shape.setOrigin(bounds.width / 2, bounds.height / 2);
}

void Figure::handleEvent(sf::Event event) {
	switch (event.type) {
	case(sf::Event::MouseWheelScrolled): {
		float delta = event.mouseWheelScroll.delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			shape.rotate(delta*10);
		}
		else{
			float newScale = shape.getScale().x*(1 + delta);
			std::cout << newScale;
			if (newScale > 0.1) {
				shape.scale(1 + delta, 1 + delta);
			}
		}
		break;
	}
	}
}

void Figure::update(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		shape.move(0, -speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		shape.move(0, speed);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		shape.move(-speed, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		shape.move(speed, 0);
	}
}

void Figure::render(sf::RenderWindow& window) {
	window.draw(shape);
}
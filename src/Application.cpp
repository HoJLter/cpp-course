#include "Application.h"

Application::Application(sf::Vector2i size) {
	window.create(sf::VideoMode(windowSize.x, windowSize.y), "VISUALIZATION");
	windowSize = size;
}

Application::Application() {
	window.create(sf::VideoMode(400, 400), "VISUALIZATION");
}

int Application::render(){
	return 0;
}

int Application::processEvents() {
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}
	return 0;
}

int Application::run() {
	processEvents();
	return 0;
}
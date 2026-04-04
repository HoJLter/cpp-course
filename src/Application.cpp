#include "Application.h"

Application::Application(uint16_t width, uint16_t height) {
	window.create(sf::VideoMode(width, height), "VISUALIZATION");
	this->width = width;
	this->height = height;
}

Application::Application() {
	window.create(sf::VideoMode(400, 400), "VISUALIZATION");
}

void Application::processEvents() {
	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		figure.handleEvent(event);
	}	
}

void Application::update() {
	figure.update();
}

void Application::render() {
	window.clear();

	figure.render(window);
	
	window.display();
}

void Application::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}
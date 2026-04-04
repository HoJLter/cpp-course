#include "Application.h"

Application::Application(uint16_t width, uint16_t height):
	start({ 700, 100 }, { 100, 400 }, "WASSUP")
{
	window.create(sf::VideoMode(width, height), "VISUALIZATION");
	this->width = width;
	this->height = height;
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
	start.render(window);
	
	window.display();
}

void Application::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}
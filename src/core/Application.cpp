#include "core/Application.h"

Application::Application(uint16_t width, uint16_t height){
	window.create(sf::VideoMode(width, height), "VISUALIZATION");
	curScene = std::make_unique<InitialScene>(window.getSize());
}

void Application::processEvents() {
	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		curScene->handleEvent(event);
	}
}

void Application::update() {
	curScene->update(window);
}

void Application::render() {
	window.clear();

	curScene->render(window);

	window.display();
}

void Application::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

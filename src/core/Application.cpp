#include "core/Application.h"
#include "utils/Log.h"

Application::Application(uint16_t width, uint16_t height):
window(sf::VideoMode(width, height), "VISUALIZATION"),
sceneManager(window){
	Log::debug("Application created");
}

void Application::processEvents() {
	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			Log::debug("Window closed");
			window.close();
		}

		sceneManager.handleEvent(event);

	}
}

void Application::update() {
	sceneManager.update();
}

void Application::render() {
	window.clear();

	sceneManager.render();

	window.display();
}

void Application::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

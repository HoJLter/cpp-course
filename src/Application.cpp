#include "Application.h"

Application::Application(uint16_t width, uint16_t height):
	start_label("Enter count of dots.", {static_cast<float>(width)/2, height-150.f}, 18),
	start({ 50, 20 }, {static_cast<float>(width)/2, height-50.f }, "START",
		[this]() {
			this->start_label.switchVisibility();
		})
{
	window.create(sf::VideoMode(width, height), "VISUALIZATION");
	uiView = window.getDefaultView();
	mainView = sf::View(sf::FloatRect(0.f, 0.f, 
		static_cast<float>(width), 
		static_cast<float>(height))
	);


}

void Application::processEvents() {
	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::Resized) {
			sf::FloatRect visibleArea(0.f, 0.f,
				static_cast<float>(event.size.width),
				static_cast<float>(event.size.height));
			sf::FloatRect uiArea(0.f, 0.f,
				static_cast<float>(event.size.width),
				static_cast<float>(event.size.height));

			mainView = sf::View(visibleArea);
			uiView = sf::View(uiArea);
			
		}

		figure.handleEvent(event);
		start.handleEvent(event);
	}	
}

void Application::update() {
	figure.update();
	start.update(window);
}

void Application::render() {
	window.clear();

	figure.render(window);
	start.render(window, uiView);
	start_label.render(window, uiView);
	
	window.display();
}

void Application::run() {
	while (window.isOpen()) {
		window.setView(mainView);
		processEvents();
		update();
		render();
	}
}
#include <SFML/Graphics.hpp>

const char *program_name = "sfml-prog";
const int window_width = 400;
const int window_height = 400;

int main (void)
{
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), program_name);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.display();
	}
	return 0;
}

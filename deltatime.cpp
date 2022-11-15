#include "deltatime.h"
#include <SFML/Graphics.hpp>



void deltatime::update() {
	sf::Clock clock;
	seconds = clock.getElapsedTime().asMilliseconds();
	clock.restart();
}

float deltatime::getSecs() {
	return seconds;
}


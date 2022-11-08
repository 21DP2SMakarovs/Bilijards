#include "nuja.h"
#include "bumba.h"
#include <SFML/Graphics.hpp>
#include <iostream>



nuja::nuja(sf::Vector2f pos, const char * file_path) {
	if (!cuetx.loadFromFile(file_path)) {
		std::cout << "Failed" << std::endl;
	}
	position = pos;
	cue.setPosition(pos);
	cue.setTexture(cuetx);
	cue.setScale(sf::Vector2f(0.5f, 0.5f));
	cue.setOrigin(sf::Vector2f(0, 14));
	cue.move(sf::Vector2f(10, 0));
	
}

void nuja::shot() {

}

void nuja::hide(bumba& cueball) {
	if (cueball.getVel().x != 0 && cueball.getVel().y != 0) {
		cue.setScale(0, 0);
	}

}

void nuja::show(std::vector<bumba> balls) {
	for (int i = 0; i < balls.size(); i++) {
		if (balls[i].getVel().x == 0 && balls[i].getVel().y == 0) {
			cue.setScale(sf::Vector2f(0.5f, 0.5f));
		}
	}
}


void nuja::draw(sf::RenderWindow& window) {
	window.draw(cue);
}

void nuja::rotate(float deg) {
	cue.setRotation(deg);
}


void nuja::setPos(sf::Vector2f pos) {
	cue.setPosition(pos);
}

sf::Vector2f nuja::getPos() {
	return sf::Vector2f(position.x, position.y);
}
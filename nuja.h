#pragma once
#include <SFML/Graphics.hpp>
#include "bumba.h"
#include <iostream>

class nuja {
private:
	sf::Vector2f position;
	sf::Texture cuetx;
	

public:
	sf::Sprite cue;
	nuja(sf::Vector2f pos, const char* file_path);
	void shot();
	void draw(sf::RenderWindow& window);
	void update();
	void setPos(sf::Vector2f pos);
	void rotate(float deg);
	void hide(bumba& cueball);
	void show(std::vector<bumba> balls);


	sf::Vector2f getPos();

	
};


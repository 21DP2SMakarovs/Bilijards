#pragma once
#include <SFML/Graphics.hpp>

class bumba
{
public:
	sf::CircleShape ball;
	
	bumba(sf::Vector2f pos, bool cball = false);
	void draw(sf::RenderWindow& window);
	void move(float power = 50);
	void update(sf::Vector2f vel);
	bool collision(bumba& b);
	bool collisionV2(float x, float y);

	bool isMoving();
	sf::Vector2f getVel();
	sf::Vector2f getPos();


private:
	bool cue_ball = false;
	bool eight_ball = false;
	float radius = 10;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float secs;

	
};


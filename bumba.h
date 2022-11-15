#pragma once
#include <SFML/Graphics.hpp>

class bumba
{
public:
	sf::CircleShape ball;

	
	bumba(sf::Vector2f pos, bool cball = false);
	void draw(sf::RenderWindow& window);
	void move();
	void update(float angle);
	bool collision(bumba& b);
	bool collisionV2(bumba& b);
	bool isMoving();
	sf::Vector2f getVel();
	sf::Vector2f getPos();
	void setPos(sf::Vector2f pos);
	bool inHole();


	void changeSecs(float sec);

	
	

private:
	float angle = 0;
	float speed = 0;
	bool cue_ball = false;
	bool eight_ball = false;
	float radius = 10;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float secs;
	float mass = 0.17;
	float hitAngle;

	
};


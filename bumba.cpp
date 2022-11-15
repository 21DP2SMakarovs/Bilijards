#include "bumba.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "deltatime.h"

#define PI 3.14159



bumba::bumba(sf::Vector2f pos, bool cball) {
	ball.setPosition(pos);
	ball.setRadius(radius);
	ball.setFillColor(sf::Color::White);
	ball.setPointCount(16);
	position = pos;
	velocity.x = 0;
	velocity.y = 0;
	if (cball) {
		cue_ball = true;
		
	}

}

void bumba::changeSecs(float sec) {
	this->secs = sec;
}


float calculateDir(float x1, float y1, float x2, float y2) {


	float radian = atan2f(y2 - y1, x2 - x1);
	float deg = radian * 180 / PI;
	//std::cout << deg << std::endl;

	return deg;
}


bool bumba::inHole() {
	bool value = false;
	if ((this->position.x - 168) * (this->position.x - 168) + (this->position.y - 165) * (this->position.y - 165) <= 28*28)
		value = true;
	else if ((this->position.x - 629) * (this->position.x - 629) + (this->position.y - 151) * (this->position.y - 151) <= 24 * 24)
		value = true;
	else if ((this->position.x - 1085) * (this->position.x - 1085) + (this->position.y - 165) * (this->position.y - 165) <= 28 * 28)
		value = true;
	else if (((this->position.x - 168) * (this->position.x - 168) + (this->position.y - 638) * (this->position.y - 638) <= 28 * 28))
		value = true;
	else if ((this->position.x - 629) * (this->position.x - 629) + (this->position.y - 649) * (this->position.y - 649) <= 24 * 24)
		value = true;
	else if (((this->position.x - 1085) * (this->position.x - 1085) + (this->position.y - 638) * (this->position.y - 638) <= 28 * 28))
		value = true;
	else
		value = false;
	return value;
}



bool bumba::collision(bumba &b) {

	bool value = false;
	if (collisionV2(b)) {
		b.angle = calculateDir(this->position.x + 9, this->position.y + 9, b.position.x + 9, b.position.y + 9);
		
		b.speed = this->speed;

		value = true;
	}
	return value;
}

bool bumba::collisionV2(bumba& b)
{
	float dist_x = (this->position.x + 9) - (b.position.x + 9);
	float dist_y = (this->position.y + 9) - (b.position.y + 9);
	float radi_sum = this->radius + b.radius;
		
	if (dist_x * dist_x + dist_y * dist_y <= radi_sum * radi_sum) 
		return true;

	return false;
}





void bumba::draw(sf::RenderWindow& window) {
	window.draw(this->ball);
}

sf::Vector2f bumba::getPos() {
	return sf::Vector2f(this->position.x, this->position.y);
}

sf::Vector2f bumba::getVel() {
	return sf::Vector2f(this->velocity.x, this->velocity.y);
}

bool bumba::isMoving() {
	bool isMoving;
	if (this->velocity.x == 0.00000f && this->velocity.y == 0.00000f) {
		isMoving = false;
	}
	else {
		isMoving = true;
	}
	return isMoving;
}


void bumba::move() { //deaccleration


	
	if (this->speed > 0) {
		this->speed -= 0.0065;
		this->velocity.x = this->speed * cos(this->angle * PI / 180);
		this->velocity.y = this->speed * sin(this->angle * PI / 180);
		
		
	}
	else {
		this->speed = 0;
		this->velocity = sf::Vector2f(0, 0);
	}

}

void bumba::update(float angle) {

	sf::Clock Deltaclock;
	secs = Deltaclock.getElapsedTime().asSeconds();




	if (cue_ball)
	{//key events for movement
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			this->speed = 4.5f;
			this->angle = angle + 180;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			this->speed = 3;
			this->angle = 90;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			this->speed = 3;
			this->angle = 180;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			this->speed = 3;
			this->angle = 0;
		}
	}

	//board_and_ball collission //x1 = 179, y1 = 177 | x2 = 1068, y2 = 627


	if (position.x <= 179.0f && position.y >= 192.0f && position.y <= 590.0f) // kreisi
	{

		position.x = 183.0f;
		this->angle = 180 - this->angle;
	}
	else if (position.y <= 177.0f && position.x >= 195.0f && position.x <= 595.0f) { // augsa 1
		position.y = 181.0f;
		this->angle = -this->angle;
	}
	else if (position.y <= 177.0f && position.x <= 1040.0f && position.x >= 640.0f) { // augsa 2
		position.y = 181.0f;
		this->angle = -this->angle;
	}
	else if (position.y >= 605.0f && position.x >= 195.0f && position.x <= 595.0f) { // apaksa 1
		position.y = 601.0f;
		this->angle = -this->angle;
	}
	else if (position.y >= 605.0f && position.x <= 1040.0f && position.x >= 640.0f) { // apaksa 2
		position.y = 601.0f;
		this->angle = -this->angle;
	}
	else if (position.x >= 1045.0f && position.y >= 192.0f && position.y <= 589.0f) // labi
	{
		position.x = 1041.0f;
		this->angle = 180 - this->angle;
	}

	
	position = position + velocity;
	ball.setPosition(position);
	move();
}

void bumba::setPos(sf::Vector2f pos) {
	this->position = pos;
}




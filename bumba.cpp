#include "bumba.h"
#include <SFML/Graphics.hpp>
#include <iostream>





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
		std::cout << "True";
	}

}

bool bumba::collision(bumba &b) {
	float dist = sqrtf((b.position.x - position.x) * (b.position.x - position.x) + (b.position.y - position.y) * (b.position.y - position.y));
	bool value = false;
	if (dist <= 18) {


		//std::cout << "Collision" << std::endl;
		if (b.velocity.x * velocity.x > 0)
		{
			float vel2 = b.velocity.x; 
			float vel1 = velocity.x;
			b.velocity.x = b.velocity.x + vel1;
			velocity.x = velocity.x - vel2;

			
		}
		else if (b.velocity.x * velocity.x < 0)
		{
			float vel2;
			vel2 = b.velocity.x;
			b.velocity.x = velocity.x;
			velocity.x = vel2;

		}
		else if (b.velocity.x == 0)
		{
			b.velocity.x = velocity.x;
			velocity.x = 0;

		}
		if (b.velocity.y * velocity.y > 0)
		{
			float vel2 = b.velocity.y;
			float vel1 = velocity.y;
			b.velocity.y = b.velocity.y + vel1;
			velocity.y = velocity.y - vel2;
			
		}
		else if (b.velocity.y * velocity.y < 0)
		{
			float vel2;
			vel2 = b.velocity.y;
			b.velocity.y = velocity.y;
			velocity.y = vel2;

		}
		else if (b.velocity.y == 0)
		{
			b.velocity.y = velocity.y;
			velocity.y = 0;

		}

		value = true;
	}
	return value;
}





void bumba::draw(sf::RenderWindow& window) {
	window.draw(ball);
}

sf::Vector2f bumba::getPos() {
	return sf::Vector2f(position.x, position.y);
}

sf::Vector2f bumba::getVel() {
	return sf::Vector2f(velocity.x, velocity.y);
}

bool bumba::isMoving() {
	bool isMoving;
	if (velocity.x == 0.00000f && velocity.y == 0.00000f) {
		isMoving = false;
	}
	else {
		isMoving = true;
	}
	return isMoving;
}


void bumba::move(float power) { //deaccleration


	//std::cout << "TIME" << x << std::endl;

	
	if (velocity.x > 0)
	{
		velocity.x = velocity.x - 50 * secs; // velocity - decrease Value * delta time (less value of dValue = higher power)
		velocity.x = (velocity.x >= 7.0f) ? 6.0f: velocity.x;
		if (velocity.x < 0)
		{
			velocity.x = 0;
		}
	}
	if (velocity.y > 0)
	{

		velocity.y = velocity.y - 50 * secs;
		velocity.y = (velocity.y >= 7.0f) ? 6.0f : velocity.y;
		if (velocity.y < 0)
		{
			velocity.y = 0;	
		}
	}
	if (velocity.x < 0)
	{
		velocity.x = velocity.x + 50 * secs;
		velocity.x = (velocity.x <= -7.0f) ? -6.0f : velocity.x;
		if (velocity.x > 0)
		{
			velocity.x = 0;
		}
	}
	if (velocity.y < 0)
	{
		velocity.y = velocity.y + 50 * secs;
		velocity.y = (velocity.y <= -7.0f) ? -6.0f : velocity.y;
		if (velocity.y > 0)
		{
			velocity.y = 0;
		}
	}
}

void bumba::update(sf::Vector2f vel) {

	sf::Clock Deltaclock;
	secs = Deltaclock.getElapsedTime().asSeconds();




	if (cue_ball)
	{//key events for movement
		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			//velocity.y = -5.0f;
			velocity.x = -vel.x;
			velocity.y = -vel.y;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			velocity.y = 5.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			velocity.x = -5.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			velocity.x = 5.0f;
		}
	}

	//board_and_ball collission //x1 = 179, y1 = 177 | x2 = 1068, y2 = 627
	if (position.x <= 179.0f)
	{

		position.x = 180.0f;
		velocity.x = -velocity.x;
	}
	else if (position.y <= 177.0f)
	{
		position.y = 178.0f;
		velocity.y = -velocity.y;
	}
	else if (position.y >= 605.0f)
	{
		position.y = 604.0f;
		velocity.y = -velocity.y;
	}
	else if (position.x >= 1045.0f)
	{
		position.x = 1044.0f;
		velocity.x = -velocity.x;
	}

	//if (cue_ball) {
	//	std::cout << "vel.x - " << velocity.x << " vel.y - " << velocity.y << " clock: " << secs << std::endl;
	//}
	std::cout << "vel.x - " << velocity.x << " vel.y - " << velocity.y << " clock: " << secs << std::endl;
	position = position + velocity;
	ball.setPosition(position);

	secs = Deltaclock.restart().asSeconds();
	move();
}






#include <iostream>
#include <SFML/Graphics.hpp>
#include "bumba.h"
#include "nuja.h"


#define PI 3.14159
//declare window


//declare func
float calculateDir(bumba& cueball, sf::RenderWindow& window);
sf::Vector2f calculatePoint(bumba& cueball, sf::RenderWindow& window);
sf::Vector2f calculateVelocityDir(nuja& nuja, bumba& cueball, sf::RenderWindow& window);

//declare ball stuff



int main() {

	sf::RenderWindow window(sf::VideoMode(1250, 800), "Davai strada", sf::Style::Titlebar | sf::Style::Close);
	sf::Event e;
	
	sf::Clock DeltaClock;
	sf::Time frameTime;

	//colors
	sf::Color white(255, 255, 255, 255);
	sf::Color green(0, 200, 0, 255);
	sf::Color red(255, 0, 0);
	sf::Color light_bluish(74, 98, 237);
	sf::Color dark_bluish(1, 23, 145);


	sf::Vertex background[] = { // BG
		sf::Vertex(sf::Vector2f(0, 0), light_bluish),
		sf::Vertex(sf::Vector2f(1500, 0), light_bluish),
		sf::Vertex(sf::Vector2f(1500, 800), dark_bluish),
		sf::Vertex(sf::Vector2f(0, 800), dark_bluish)
	};

	sf::ConvexShape powerOutline;
	powerOutline.setPointCount(3);
	powerOutline.setPoint(0, sf::Vector2f(10, 250));
	powerOutline.setPoint(1, sf::Vector2f(10, 550));
	powerOutline.setPoint(2, sf::Vector2f(80, 550));
	powerOutline.setFillColor(sf::Color::Transparent); //fill with transparent color
	powerOutline.setOutlineColor(white); //outline
	powerOutline.setOutlineThickness(2.0f); //outline thicc
	
	// TODO: Make vertex for power-o-meter 
	//code


	sf::Texture table;
	if (!table.loadFromFile("table.png"))
		return -1;

	sf::Sprite TextureTable;
	TextureTable.setTexture(table);
	//TextureTable.setFillColor(red);
	TextureTable.setPosition(sf::Vector2f(113, 111));
	TextureTable.setScale(0.97, 0.97);
	//TextureTable.setSize(sf::Vector2f(1051, 600));



	
	/*sf::RectangleShape Table; // Playground Table
	Table.setFillColor(green);
	Table.setPosition(sf::Vector2f(179, 177));
	Table.setSize(sf::Vector2f(889, 450)); //x1 = 179, y1 = 177 | x2 = 1068, y2 = 627
	Table.setOutlineColor(green); */
	//sf::Font font;
	//font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	
	/*sf::Texture galdaBilde; // Table Image
	galdaBilde.loadFromFile("C:/Users/Bracka/source/repos/Sfmltry2/media/galds.jpg");  ar shito es velak tiksu gala
	sf::Sprite galds(galdaBilde);
	galds.setPosition(55, 50);
	galds.setScale(sf::Vector2f(1.2, 1.2)); */

	//cue stuff
	nuja cue(sf::Vector2f(200, 200), "cue.png");

	//ball stuff
	
	bumba cueball(sf::Vector2f(300, 400), true);
	
	bumba ball1(sf::Vector2f(755, 400));
	bumba ball2(sf::Vector2f(755 + 21, 400 + 11));
	bumba ball3(sf::Vector2f(755 + 21, 400 - 11));
	bumba ball4(sf::Vector2f(755 + 41, 400 + 22));
	bumba ball5(sf::Vector2f(755 + 41, 400));

	std::vector<bumba> b = {
		cueball,
		ball1,
		ball2,
		ball3,
		ball4,
		ball5
	};
	








	window.setFramerateLimit(60);

	



	while (window.isOpen()) { // window is open
		while (window.pollEvent(e)) { // e = event | event processing 
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
				break;
			//case sf::Event::KeyPressed:
			//	cueball.setVelocity(calculateVelocityDir(cue, cueball, window));
			//	break;
			}
		}

		window.clear(); //clear everything
		window.draw(background, 4, sf::Quads); // draw background

		//table stuff
		window.draw(TextureTable); // Texture
		//window.draw(Table); //playground
		window.draw(powerOutline); //outline for power-o-meter




		
		//balls



		for (int i = 0; i < b.size(); i++) {

			b[i].draw(window);
			b[i].update(calculateVelocityDir(cue, b[0], window));
			for (int j = 0; j < b.size(); j++) {
				if (j != i) {
					b[i].collision(b[j]);
				}
			}
			cue.setPos(calculatePoint(b[0], window));
			cue.rotate(calculateDir(b[0], window));

			


		}

		sf::CircleShape punkts;
		punkts.setRadius(1.0f);
		punkts.setFillColor(sf::Color::Red);
		punkts.setPosition(sf::Vector2f(b[0].getPos().x + 9, b[0].getPos().y + 9));



		bool state = true;

		for (int i = 0; i < b.size(); i++) {
			if (b[i].isMoving()) {
				state = false;
				break;
			}
			
		}



		if (state) {
			cue.draw(window);
		}

		//cue
		//cue.draw(window);

		//cue.setPos(calculatePoint(cueball, window));
		//cue.rotate(calculateDir(cueball, window));

		//calculateDir(cueball, window);
		//calculatePoint(cueball, window);

		window.draw(punkts);
		window.display();
		sf::Time frameTime = DeltaClock.restart();
	}

	

}

// define func
float calculateDir(bumba& cueball, sf::RenderWindow& window) {
	
	float x1 = cueball.getPos().x + 10;
	float y1 = cueball.getPos().y + 10;
	float x2 = sf::Mouse::getPosition(window).x;
	float y2 = sf::Mouse::getPosition(window).y;

	float radian = atan2f(y2 - y1, x2 - x1);
	float deg = radian * 180 / PI;
	//std::cout << deg << std::endl;

	return deg;
}

sf::Vector2f calculatePoint(bumba& cueball, sf::RenderWindow& window) {
	float cx = cueball.getPos().x + 10;
	float cy = cueball.getPos().y + 10;
	float r = 15;

	float degree = calculateDir(cueball, window) * PI / 180;

	float x = cx + r * cos(degree);
	float y = cy + r * sin(degree);

	//std::cout << "x: " << x << " y: " << y << std::endl;

	return sf::Vector2f(x, y);

}

sf::Vector2f calculateVelocityDir(nuja& nuja, bumba& cueball, sf::RenderWindow& window) {

	float x1 = cueball.getPos().x + 10;
	float y1 = cueball.getPos().y + 10;
	float x2 = sf::Mouse::getPosition(window).x;
	float y2 = sf::Mouse::getPosition(window).y;


	
	float power = 10;
	float vx = power * cos((calculateDir(cueball, window) * PI / 180));
	float vy = power * sin((calculateDir(cueball, window) * PI / 180));

	//std::cout << vx << " " << vy << std::endl;

	return sf::Vector2f(vx, vy);
}



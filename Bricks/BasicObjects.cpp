#include "BasicObjects.h"
#include <iostream> 
#include "Display.h"
using namespace std;
//ALONB - what is the difference between .h and .hpp?

extern sf::RenderWindow * pWindow; //ALONB - temp..


void BasicObjects::init(sf::Vector2i xi_screenSize)
{
	//Walls:
	cout << "Initializing game objects. Screen Resolution [x,y] [" << xi_screenSize.x << "," << xi_screenSize.y << "]" << endl;

	sf::Vector2i speed(0, 0);
	sf::Vector2f dimensions(xi_screenSize.x*GAME_OBJECTS_WALL_WIDTH_RATIO, xi_screenSize.y*GAME_OBJECTS_WALL_THIKNESS_RATIO);
	sf::Vector2f position(xi_screenSize.x*(1-GAME_OBJECTS_WALL_WIDTH_RATIO)/2, xi_screenSize.y*(1 - GAME_OBJECTS_WALL_HEIGHT_RATIO));

	wallObj.ceiling.setRectangleCharacteristics(&wallObj.celingShape, position, speed, dimensions, GAME_OBJECTS_WALL_COLOR);

	dimensions.x = xi_screenSize.y*GAME_OBJECTS_WALL_THIKNESS_RATIO;
	dimensions.y = xi_screenSize.y*(GAME_OBJECTS_WALL_HEIGHT_RATIO);


	wallObj.left.setRectangleCharacteristics(&wallObj.leftShape, position, speed, dimensions, GAME_OBJECTS_WALL_COLOR);
	position.x += (xi_screenSize.x*GAME_OBJECTS_WALL_WIDTH_RATIO - xi_screenSize.y*GAME_OBJECTS_WALL_THIKNESS_RATIO);

	wallObj.right.setRectangleCharacteristics(&wallObj.rightShape, position, speed, dimensions, GAME_OBJECTS_WALL_COLOR);

	wallObj.addBasicShape(&wallObj.ceiling);
	wallObj.addBasicShape(&wallObj.left);
	wallObj.addBasicShape(&wallObj.right);
	refreshList.push_front(&wallObj);

	//Paddle:

	dimensions.x = xi_screenSize.x *GAME_OBJECTS_PADDLE_WIDTH_RATIO;
	dimensions.y = xi_screenSize.y *GAME_OBJECTS_PADDLE_VERTICAL_THICKNESS_RATIO;
	position.y = xi_screenSize.y *GAME_OBJECTS_PADDLE_VERTICAL_HEIGHT;
	position.x = (xi_screenSize.x - dimensions.x)/2;
	paddleObj.main.setRectangleCharacteristics(&paddleObj.mainShape, position, speed, dimensions, GAME_OBJECTS_PADDLE_COLOR );
	paddleObj.addBasicShape(&paddleObj.main);
	refreshList.push_front(&paddleObj);

	//Ball:
	float radius = 100;
	ballObj.main.setCircleCharacteristics(&ballObj.mainShape, position, speed, radius, GAME_OBJECTS_BALL_COLOR);
	ballObj.addBasicShape(&ballObj.main);
	refreshList.push_front(&ballObj);

}


void basicObjectCommon::setCircleCharacteristics(sf::CircleShape* xi_pShape, sf::Vector2f xi_centerLocation, sf::Vector2i xi_speed, float xi_radius, sf::Color xi_color) { //TODO: ADD COLOR
	centerLocation = xi_centerLocation;
	speed = xi_speed;
	radius = xi_radius;
	cout << "set c" << endl;
	xi_pShape->setPosition(0, 150);
	xi_pShape->setRadius(100.f);
	xi_pShape->setFillColor(xi_color);
	pShape = xi_pShape;
}

void basicObjectCommon::setRectangleCharacteristics(sf::RectangleShape* xi_pShape, sf::Vector2f xi_centerLocation, sf::Vector2i xi_speed, sf::Vector2f xi_dimensions, sf::Color xi_color) {
	centerLocation = xi_centerLocation;
	speed = xi_speed;
	dimensions = xi_dimensions;
	xi_pShape->setSize(xi_dimensions);
	xi_pShape->setPosition(xi_centerLocation);
	xi_pShape->setFillColor(xi_color);
	pShape = xi_pShape;
}
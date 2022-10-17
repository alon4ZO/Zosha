#include "BasicObjects.h"
#include <iostream> 
#include "Display.h"
using namespace std;
//ALONB - what is the difference between .h and .hpp?



void BasicObjects::init(sf::Vector2i xi_screenSize)
{
	//Walls:
	cout << "Initializing game objects. Screen Resolution [x,y] [" << xi_screenSize.x << "," << xi_screenSize.y << "]" << endl;

	sf::Vector2f speed(0, 0);
	sf::Vector2f dimensions;
	sf::Vector2f position;
	sf::Vector2f screenSize((float)xi_screenSize.x, (float)xi_screenSize.y);

	dimensions.x = (float)(int)(screenSize.x*GAME_OBJECTS_GAME_WIN_WIDTH_RATIO);
	dimensions.y = (float)(int)(screenSize.y*GAME_OBJECTS_GAME_WIN_HEIGHT_RATIO);
	position.x = (float)(int)(screenSize.x*(1 - GAME_OBJECTS_GAME_WIN_WIDTH_RATIO) / 2);
	position.y = (float)(int)(screenSize.y*(1 - GAME_OBJECTS_GAME_WIN_HEIGHT_RATIO));

	wallObj.center.setRectangleCharacteristics(&wallObj.centerShape, position, dimensions, GAME_OBJECTS_GAME_WIN_COLOR);

	dimensions.x += (float)(int)(2 * screenSize.y*GAME_OBJECTS_GAME_WIN_FRAME_THIKNESS_RATIO);
	dimensions.y += (float)(int)(screenSize.y*GAME_OBJECTS_GAME_WIN_FRAME_THIKNESS_RATIO);
	position.x -= (float)(int)(screenSize.y*GAME_OBJECTS_GAME_WIN_FRAME_THIKNESS_RATIO);
	position.y -= (float)(int)(screenSize.y*GAME_OBJECTS_GAME_WIN_FRAME_THIKNESS_RATIO);


	wallObj.outer.setRectangleCharacteristics(&wallObj.outerShape, position, dimensions, GAME_OBJECTS_GAME_WIN_FRAME_COLOR);
	wallObj.addBasicShape(&wallObj.outer);
	wallObj.addBasicShape(&wallObj.center);
	allGamePieces.push_back(&wallObj);




	//Paddle:

	dimensions.x = (float)(int)(screenSize.x *GAME_OBJECTS_PADDLE_WIDTH_RATIO);
	dimensions.y = (float)(int)(screenSize.y *GAME_OBJECTS_PADDLE_VERTICAL_THICKNESS_RATIO);
	position.y = (float)(int)(screenSize.y *GAME_OBJECTS_PADDLE_VERTICAL_HEIGHT);
	position.x = (float)(int)((screenSize.x - dimensions.x) / 2);
	paddleObj.speed.x = GAME_OBJECTS_PADDLE_REGULAR_SPEED;

	paddleObj.farthestLeftLocationOfFirstShape = wallObj.center.getShape()->getPosition().x;
	paddleObj.farthestRightLocationOfFirstShape = wallObj.center.getShape()->getPosition().x + wallObj.centerShape.getSize().x - dimensions.x;
	paddleObj.main.setRectangleCharacteristics(&paddleObj.mainShape, position, dimensions, GAME_OBJECTS_PADDLE_COLOR);
	paddleObj.addBasicShape(&paddleObj.main);

	allGamePieces.push_back(&paddleObj);


	//Ball:
	float radius = (float)(int)(screenSize.y *GAME_OBJECTS_BALL_RADIUS_RATIO);
	position.x = (float)(int)(screenSize.x / 2);
	ballObj.main.setCircleCharacteristics(&ballObj.mainShape, position, radius, GAME_OBJECTS_BALL_COLOR);
	ballObj.addBasicShape(&ballObj.main);
	ballObj.speed.x = GAME_OBJECTS_BALL_DEFAULT_SPEED_X;
	ballObj.speed.y = GAME_OBJECTS_BALL_DEFAULT_SPEED_Y;


	ballObj.farthestRightLocationOfFirstShape = wallObj.center.getShape()->getPosition().x + wallObj.centerShape.getSize().x - radius;
	ballObj.farthestLeftLocationOfFirstShape = wallObj.center.getShape()->getPosition().x + radius;
	ballObj.farthestUpLocationOfFirstShape = wallObj.center.getShape()->getPosition().y + radius;
	allGamePieces.push_back(&ballObj);
}



void basicObjectCommon::setCircleCharacteristics(sf::CircleShape* xi_pShape, sf::Vector2f xi_centerLocation, float xi_radius, sf::Color xi_color) { //TODO: ADD COLOR //ALONB - the locations is not "Center Location".
	cout << "set c" << endl;
	xi_pShape->setPosition(xi_centerLocation);
	xi_pShape->setRadius(xi_radius);
	xi_pShape->setFillColor(xi_color);
	pShape = xi_pShape;
}

void basicObjectCommon::setRectangleCharacteristics(sf::RectangleShape* xi_pShape, sf::Vector2f xi_centerLocation, sf::Vector2f xi_dimensions, sf::Color xi_color) {
	xi_pShape->setSize(xi_dimensions);
	xi_pShape->setPosition(xi_centerLocation);
	xi_pShape->setFillColor(xi_color);
//	speed = xi_speed;
	pShape = xi_pShape;
}

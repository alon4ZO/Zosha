#include "BasicObjects.h"
#include <iostream> 
#include "Display.h"
using namespace std;
//ALONB - what is the difference between .h and .hpp?




void BasicObjects::init(sf::Vector2i xi_screenSize)
{
	//Walls:
	//gameFrame.init();
	cout << "Initializing game objects. Screen Resolution [x,y] [" << xi_screenSize.x << "," << xi_screenSize.y << "]" << endl;

	sf::Vector2f speed(0, 0);
	sf::Vector2f dimensionsWindow;
	sf::Vector2f dimensionsFrame;
	sf::Vector2f dimensionsPaddle;
	sf::Vector2f positionWindow;
	sf::Vector2f positionOffsetFrame;
	sf::Vector2f positionPaddle;
	sf::Vector2f screenSize((float)xi_screenSize.x, (float)xi_screenSize.y);

	dimensionsWindow.x = (float)(int)(screenSize.x*GAME_OBJECTS_GAME_WIN_WIDTH_RATIO);
	dimensionsWindow.y = (float)(int)(screenSize.y*GAME_OBJECTS_GAME_WIN_HEIGHT_RATIO);
	positionWindow.x = (float)(int)(screenSize.x*(1 - GAME_OBJECTS_GAME_WIN_WIDTH_RATIO) / 2);
	positionWindow.y = (float)(int)(screenSize.y*(1 - GAME_OBJECTS_GAME_WIN_HEIGHT_RATIO));
	gameFrame.setVirtualLocation(positionWindow); //According to inner window.
	gameFrame.setVirtualDimensions(dimensionsWindow); //According to inner window.


	dimensionsFrame.x = dimensionsWindow.x + (float)(int)(2 * screenSize.y*GAME_OBJECTS_GAME_WIN_FRAME_THIKNESS_RATIO);
	dimensionsFrame.y = dimensionsWindow.y + (float)(int)(screenSize.y*GAME_OBJECTS_GAME_WIN_FRAME_THIKNESS_RATIO);
	positionOffsetFrame.x = (float)(int)(-screenSize.y*GAME_OBJECTS_GAME_WIN_FRAME_THIKNESS_RATIO);
	positionOffsetFrame.y = (float)(int)(-screenSize.y*GAME_OBJECTS_GAME_WIN_FRAME_THIKNESS_RATIO);

	gameFrame.addRectangleShape(dimensionsFrame, GAME_OBJECTS_GAME_WIN_FRAME_COLOR, positionOffsetFrame, speed);
	gameFrame.addRectangleShape(dimensionsWindow, GAME_OBJECTS_GAME_WIN_COLOR, sf::Vector2f{ 0,0 }, speed);

	gameFrame.loadShapesToAbstractShapeList();
	allGamePieces.push_back(&gameFrame);


	//Paddle:
	dimensionsPaddle.x = (float)(int)(screenSize.x *GAME_OBJECTS_PADDLE_WIDTH_RATIO);
	dimensionsPaddle.y = (float)(int)(screenSize.y *GAME_OBJECTS_PADDLE_VERTICAL_THICKNESS_RATIO);
	positionPaddle.y = (float)(int)(screenSize.y *GAME_OBJECTS_PADDLE_VERTICAL_HEIGHT);
	positionPaddle.x = (float)(int)((screenSize.x - dimensionsPaddle.x) / 2);
	paddleObj.setVirtualDimensions(dimensionsPaddle);
	paddleObj.setVirtualLocation(positionPaddle);

	speed.x = GAME_OBJECTS_PADDLE_REGULAR_SPEED;

	paddleObj.setMotionLimitLeft(gameFrame.getVirtualLocation().x);
	paddleObj.setMotionLimitRight(gameFrame.getVirtualLocation().x + gameFrame.getVirtualDimensions().x);

	paddleObj.addRectangleShape(dimensionsPaddle, GAME_OBJECTS_PADDLE_COLOR, { 0,0 }, speed);
	paddleObj.loadShapesToAbstractShapeList();
	allGamePieces.push_back(&paddleObj);


	//Ball:
	float radius = (float)(int)(screenSize.y *GAME_OBJECTS_BALL_RADIUS_RATIO);

	ballObj.setVirtualDimensions( { radius, radius }); 
	ballObj.setVirtualLocation( { (float)(int)(screenSize.x / 2), (float)(int)(screenSize.y / 2) });
	ballObj.addCircleShape(radius, GAME_OBJECTS_BALL_COLOR, { 0,0 }, { GAME_OBJECTS_BALL_DEFAULT_SPEED_X , GAME_OBJECTS_BALL_DEFAULT_SPEED_Y });
	ballObj.loadShapesToAbstractShapeList(); //ALONB - do it inside the functions, but watch out not to do it with a pointer that does not exist anymore.

	ballObj.setMotionLimitLeft(0);
	ballObj.setMotionLimitRight(0);
	ballObj.setMotionLimitTop(0);
	ballObj.setMotionLimitBottom(0);
	allGamePieces.push_back(&ballObj);
}



void virtualObject::addCircleShape(float xi_radius, sf::Color xi_color, sf::Vector2f xi_offsetFromVirtualLocation, sf::Vector2f xi_speed) {
	sf::CircleShape circleShape;
	circleShape.setRadius(xi_radius);
	circleShape.setPosition(this->virtualLocation + xi_offsetFromVirtualLocation);
	circleShape.setFillColor(xi_color);
	circleShapesList.push_back(circleShape);
	speed = xi_speed;

}

void virtualObject::addRectangleShape(sf::Vector2f xi_dimensions, sf::Color xi_color, sf::Vector2f xi_offsetFromVirtualLocation, sf::Vector2f xi_speed) {
	sf::RectangleShape rectangleShape;
	rectangleShape.setSize(xi_dimensions);
	rectangleShape.setPosition(this->virtualLocation + xi_offsetFromVirtualLocation);
	rectangleShape.setFillColor(xi_color);
	rectangleShapesList.push_back(rectangleShape);
	speed = xi_speed;
}

void virtualObject::loadShapesToAbstractShapeList() //Dont need?
{
	for (auto const& x : circleShapesList)
	{
		shapesList.push_back((sf::Shape *)&x);
	}
	for (auto const& x : rectangleShapesList)
	{
		cout << "load" << endl;
		shapesList.push_back((sf::Shape *)&x);
	}
}

void BasicObjects::drawAllBasicShapes()
{
	for (auto const& i : allGamePieces)
	{
		for (auto const& x : i->getShapeList())
		{
			drawFunc(x);
		}
	}
}




void BasicObjects::movePaddleLeft()
{
	paddleObj.setSpeed ({ -min((float)GAME_OBJECTS_PADDLE_REGULAR_SPEED, (paddleObj.getVirtualLocation().x - gameFrame.getVirtualLocation().x)),0 });
	paddleObj.moveStep();
}

void BasicObjects::movePaddleRight()
{
	paddleObj.setSpeed({
		min( (float)GAME_OBJECTS_PADDLE_REGULAR_SPEED,
		gameFrame.getVirtualLocation().x + gameFrame.getVirtualDimensions().x - (paddleObj.getVirtualLocation().x + paddleObj.getVirtualDimensions().x))
		,0 });
	paddleObj.moveStep();
}


void BasicObjects::moveBall()
{
	ballObj.moveStep();
	//if 

}

void virtualObject::moveStep()
{
	//cout << "M1" << endl;
	virtualLocation += speed;
	for (auto const& i : shapesList)
	{
		cout << "M2" << endl;
		i->move(speed.x, speed.y);
	}
}


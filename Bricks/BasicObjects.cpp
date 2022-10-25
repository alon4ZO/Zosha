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

	dimensionsWindow.x = dimensionsWindow.x - (float)((int)dimensionsWindow.x % 140); //ALONB - try to remove.
	gameFrame.setVirtualLocation(positionWindow); //According to inner window.
	gameFrame.setVirtualDimensions(dimensionsWindow); //According to inner window.

	cout << "Game Window Dimensions [x,y] [" << gameFrame.getVirtualDimensions().x << "," << gameFrame.getVirtualDimensions().y << "]" << endl;
	cout << "Game Window Location [x] [" << gameFrame.getVirtualLocation().x << endl;



	dimensionsFrame.x = dimensionsWindow.x + (float)(int)(2 * dimensionsWindow.y*GAME_OBJECTS_GAME_WIN_FRAME_THIKNESS_RATIO);
	dimensionsFrame.y = dimensionsWindow.y + (float)(int)(dimensionsWindow.y*GAME_OBJECTS_GAME_WIN_FRAME_THIKNESS_RATIO);
	positionOffsetFrame.x = (float)(int)(-dimensionsWindow.y*GAME_OBJECTS_GAME_WIN_FRAME_THIKNESS_RATIO);
	positionOffsetFrame.y = (float)(int)(-dimensionsWindow.y*GAME_OBJECTS_GAME_WIN_FRAME_THIKNESS_RATIO);

	gameFrame.addRectangleShape(dimensionsFrame, GAME_OBJECTS_GAME_WIN_FRAME_COLOR, positionOffsetFrame);
	gameFrame.addRectangleShape(dimensionsWindow, GAME_OBJECTS_GAME_WIN_COLOR, sf::Vector2f{ 0,0 });

	gameFrame.loadShapesToAbstractShapeList();
	allGamePieces.push_back(&gameFrame);


	//Paddle:
	dimensionsPaddle.x = (float)(int)(dimensionsWindow.x *GAME_OBJECTS_PADDLE_WIDTH_RATIO);
	dimensionsPaddle.y = (float)(int)(dimensionsWindow.y *GAME_OBJECTS_PADDLE_VERTICAL_THICKNESS_RATIO);
	positionPaddle.y = (float)(int)(positionWindow.y + dimensionsWindow.y*GAME_OBJECTS_PADDLE_VERTICAL_HEIGHT);
	positionPaddle.x = (float)(int)(positionWindow.x +(dimensionsWindow.x - dimensionsPaddle.x) / 2);
	paddleObj.setVirtualDimensions(dimensionsPaddle);
	paddleObj.setVirtualLocation(positionPaddle);

	speed.x = GAME_OBJECTS_PADDLE_PIXELS_PER_US;

	paddleObj.setMotionLimitLeft(gameFrame.getVirtualLocation().x);
	paddleObj.setMotionLimitRight(gameFrame.getVirtualLocation().x + gameFrame.getVirtualDimensions().x - dimensionsPaddle.x);

	paddleObj.addRectangleShape(dimensionsPaddle, GAME_OBJECTS_PADDLE_COLOR, { 0,0 });
	paddleObj.setSpeed( GAME_OBJECTS_PADDLE_PIXELS_PER_US , 0); //ALONB - use const not 90
	paddleObj.loadShapesToAbstractShapeList();
	allGamePieces.push_back(&paddleObj);


	//Ball:
	float radius = (float)(int)(dimensionsWindow.x *GAME_OBJECTS_BALL_RADIUS_RATIO);

	ballObj.setVirtualDimensions( { 2*radius, 2*radius }); 
	ballObj.setVirtualLocation( { (float)(int)(positionWindow.x + dimensionsWindow.x/2), (float)(int)(dimensionsWindow.y / 2) });

	
	ballObj.setSpeed(GAME_OBJECTS_BALL_PIXELS_PER_US_VECTOR, GAME_OBJECTS_BALL_INIT_ANGLE);
	ballObj.addCircleShape(radius, GAME_OBJECTS_BALL_COLOR, { 0,0 });

	ballObj.setMotionLimitLeft(gameFrame.getVirtualLocation().x);
	ballObj.setMotionLimitRight(gameFrame.getVirtualLocation().x + gameFrame.getVirtualDimensions().x - ballObj.getVirtualDimensions().x);
	ballObj.setMotionLimitTop(gameFrame.getVirtualLocation().y);
	ballObj.setMotionLimitBottom(paddleObj.getVirtualLocation().y - ballObj.getVirtualDimensions().y);
	
	ballObj.loadShapesToAbstractShapeList(); //ALONB - do it inside the functions, but watch out not to do it with a pointer that does not exist anymore.
	allGamePieces.push_back(&ballObj);
}



void virtualObject::addCircleShape(float xi_radius, sf::Color xi_color, sf::Vector2f xi_offsetFromVirtualLocation) { //ALONB - speed should be with API and not per shape. (so remove it from this declaration.
	sf::CircleShape circleShape;
	circleShape.setRadius(xi_radius);
	circleShape.setPosition(this->virtualLocation + xi_offsetFromVirtualLocation);
	circleShape.setFillColor(xi_color);
	circleShapesList.push_back(circleShape);

}

void virtualObject::addRectangleShape(sf::Vector2f xi_dimensions, sf::Color xi_color, sf::Vector2f xi_offsetFromVirtualLocation) {
	sf::RectangleShape rectangleShape;
	rectangleShape.setSize(xi_dimensions);
	rectangleShape.setPosition(this->virtualLocation + xi_offsetFromVirtualLocation);
	rectangleShape.setFillColor(xi_color);
	rectangleShapesList.push_back(rectangleShape);
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


void BasicObjects::reset()
{
	ballObj.setLocation({ gameFrame.getVirtualLocation().x + gameFrame.getVirtualDimensions().x/2  , gameFrame.getVirtualLocation().y *3/2 });
	ballActive = true;
}

void BasicObjects::movePaddleLeft()
{
	sf::Vector2f paddleStepProjection = paddleObj.getSpeed() * (float)timeSinceLastStepUS;
	paddleObj.moveStep({ -min((float)paddleStepProjection.x, (paddleObj.getVirtualLocation().x - gameFrame.getVirtualLocation().x)), 0 });
}

void BasicObjects::movePaddleRight()
{
	sf::Vector2f paddleStepProjection = paddleObj.getSpeed() * (float)timeSinceLastStepUS;
	paddleObj.moveStep({ min((float)paddleStepProjection.x, (paddleObj.getMotionLimitRight() - paddleObj.getVirtualLocation().x) ) , 0 });
}

void BasicObjects::moveBall()
{
	sf::Vector2f ballStepProjection = ballObj.getSpeed() * (float)timeSinceLastStepUS;
 	sf::Vector2f newProjectedLocation = ballObj.getVirtualLocation() + ballStepProjection;
	sf::Vector2f moveBall = { ballStepProjection.x, ballStepProjection.y };

	if (newProjectedLocation.x <= ballObj.getMotionLimitLeft())
	{
		moveBall.x = - ballStepProjection.x - 2 * (ballObj.getVirtualLocation().x - ballObj.getMotionLimitLeft());
		ballObj.revSpeedX();
	}

	else if (newProjectedLocation.x >= ballObj.getMotionLimitRight())
	{
		moveBall.x = -(ballStepProjection.x - 2 * (ballObj.getMotionLimitRight() - ballObj.getVirtualLocation().x));
		ballObj.revSpeedX();
	}

	else if (newProjectedLocation.y <= ballObj.getMotionLimitUp())
	{
		moveBall.y = -ballStepProjection.y - 2 * (ballObj.getVirtualLocation().y - ballObj.getMotionLimitUp());
		ballObj.revSpeedY();
	}

	else if (newProjectedLocation.y >= ballObj.getMotionLimitBottom() && ballActive)
	{
		ballActive = false;
		float returnAngleRelativeToTop = 0;
		if (BasicObjects::getBallReturnAngleDuringPaddleHit(ballObj.getVirtualLocation().x + ballObj.getVirtualDimensions().x/2, paddleObj.getVirtualLocation().x, paddleObj.getVirtualLocation().x + paddleObj.getVirtualDimensions().x, &returnAngleRelativeToTop))
		{
			moveBall = { 0,0 };
 			ballObj.setSpeed(GAME_OBJECTS_BALL_PIXELS_PER_US_VECTOR, (returnAngleRelativeToTop-90));
			ballActive = true;
			cout << returnAngleRelativeToTop << endl;
		}		
	}

 	ballObj.moveStep(moveBall);
}

bool BasicObjects::getBallReturnAngleDuringPaddleHit(float xi_BallTouchPoint, float xi_PaddleLeftPoint, float xi_PaddleRightPoint, float * xo_pReturnAngleRelativeToTop)
{
	if (xi_BallTouchPoint < xi_PaddleLeftPoint || xi_BallTouchPoint > xi_PaddleRightPoint)
	{
		return false;
	}

	*xo_pReturnAngleRelativeToTop = GAME_OBJECTS_BALL_MAX_ANGLE * (xi_BallTouchPoint - (xi_PaddleLeftPoint + xi_PaddleRightPoint)/2) / (paddleObj.getVirtualDimensions().x / 2);
	return true;
}

void virtualObject::moveStep(sf::Vector2f xi_step)
{
	virtualLocation += xi_step;
	for (auto const& i : shapesList)
	{
		i->move(xi_step.x, xi_step.y);
	}
}

void virtualObject::setLocation(sf::Vector2f xi_location)
{
	virtualLocation = xi_location;
	for (auto const& i : shapesList)
	{
		i->setPosition(xi_location.x, xi_location.y);
	}
}

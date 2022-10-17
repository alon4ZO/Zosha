#ifndef __ANIMATE__
#define __ANIMATE__
#include "BasicObjects.h"

class Animate : public BasicObjects
{
	std::function<void(sf::Shape *)> drawFunc;
	std::function<void(sf::Shape *)> moveFunc;


public:
	void registerDrawFunction(std::function<void(sf::Shape *)> xi_function) { drawFunc = xi_function; }
	void registerMoveFunction(std::function<void(sf::Shape *)> xi_function) { moveFunc = xi_function; }
	void drawAllBasicShapes();
	void movePaddleLeft();
	void movePaddleRight();
	void moveBall();
};


#endif __ANIMATE__


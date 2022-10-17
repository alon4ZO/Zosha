
#include "Animate.h"
#include <iostream>



using namespace std;

void Animate::drawAllBasicShapes()
{
	for (auto const& i : allGamePieces)
	{
		for (auto const& x : i->getShapeList())
			drawFunc(x->getShape());
	}

}

void Animate::movePaddleLeft()
{
	for (auto const& i : Animate::paddleObj.getShapeList())
	{
		i->getShape()->move(-min(paddleObj.speed.x, i->getShape()->getPosition().x - paddleObj.farthestLeftLocationOfFirstShape), paddleObj.speed.y);
		drawFunc(i->getShape());
	}
}

void Animate::movePaddleRight()
{
	for (auto const& i : Animate::paddleObj.getShapeList())
	{
		i->getShape()->move(min(paddleObj.speed.x, paddleObj.farthestRightLocationOfFirstShape - i->getShape()->getPosition().x), paddleObj.speed.y); //This works with multiple shapes??? don't think so. ALONB
		drawFunc(i->getShape());
	}
}


void Animate::moveBall()
{
	for (auto const& i : Animate::ballObj.getShapeList())
	{
		i->getShape()->move(ballObj.speed.x, -ballObj.speed.y);
		drawFunc(i->getShape());

	//	if (i->getShape()->getPosition().x) //ALONB - do this relative to the entire shape position and not just position of the first shape..
	}

}




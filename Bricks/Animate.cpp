
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
		//cout << i->getShape()->getPosition().x << endl;
		//cout << paddleObj.farthestLeftLocationOfFirstShape << endl << endl;


	//	cout << "moving left" << endl;
		i->getShape()->move(-min(paddleObj.speed.x, i->getShape()->getPosition().x - paddleObj.farthestLeftLocationOfFirstShape), paddleObj.speed.y);
		drawFunc(i->getShape());
	}
}

void Animate::movePaddleRight()

{

	for (auto const& i : Animate::paddleObj.getShapeList())
	{
		//cout << i->getShape()->getPosition().x << endl;
		//cout << paddleObj.farthestRightLocationOfFirstShape << endl << endl;

	//	if (i->getShape()->getPosition().x >= paddleObj.farthestRightLocationOfFirstShape)
	//		return;

	//	cout << "moving right" << endl;
		i->getShape()->move(min(paddleObj.speed.x, paddleObj.farthestRightLocationOfFirstShape - i->getShape()->getPosition().x), paddleObj.speed.y);
		drawFunc(i->getShape());
	}
}




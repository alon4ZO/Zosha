#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <windows.h>  
#include<thread>
#include "Display.h"
#include "BasicObjects.h"
#include "Engine.h"
#include <chrono>
#include <thread>

using namespace std;


sf::RenderWindow * pWindow; //ALONB - temp..



void Engine::init(Animate *xi_pAnimate, Display * display)
{

	//std::list<combinedObjGeneric*> list = xi_pObjects->getrefreshList();

	//for (std::list<combinedObjGeneric*>::iterator listIt = list.begin(); listIt != list.end(); listIt++)
	//{
	//	std::list<basicObjectCommon *> shapeList = (*listIt)->getShapeList();
	//	cout << "Size" << shapeList.size() << endl;
	//	for (std::list<basicObjectCommon*>::iterator listShapesInComplexObject = shapeList.begin(); listShapesInComplexObject != shapeList.end(); listShapesInComplexObject++)
	//	{
	//		cout << "Loading Shape" << endl;
	//	    sf::Shape * s = (*listShapesInComplexObject)->getShape();
	//		xi_pObjects->getDrawFunction()(s);
	//	}
	//}
	xi_pAnimate->drawAllBasicShapes();
	//pWindow->display();
	display->display();

	pWindow = display->getWindow();
	pWindow->setActive(false);
	//std::thread t1(&Engine::gameThread, Engine(), xi_pAnimate, display);

//	t1.join();
	while (1)
	{

		sf::Event event; //why do i have to poll the event?
		pWindow->pollEvent(event);

		if (GetKeyState(VK_LEFT) & 0x8000) {
			xi_pAnimate->movePaddleLeft();
		}

		if (GetKeyState(VK_RIGHT) & 0x8000) {
			xi_pAnimate->movePaddleRight();
		}

		xi_pAnimate->moveBall();

		pWindow->clear();
		xi_pAnimate->drawAllBasicShapes();
		display->display();

		std::this_thread::sleep_for(std::chrono::milliseconds(STEP_INTERVAL_MS));
	}
}


void Engine::gameThread(Animate * xi_pAnimate, Display * display) {
	pWindow->setActive(true);

}

	//while (1)
	//{
	//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//	//cout << "It" << endl;
	//		cout << "X" << endl;
	//	if (GetKeyState('A') & 0x8000)
	//	{
	//		cout << "A" << endl;
	//		xi_pAnimate->movePaddleLeft();
	//		cout << "B" << endl;
	//		pWindow->clear();
	//		cout << "C" << endl;
	//		display->display();

	//		
	//	}
	//	else if (GetKeyState('S') & 0x8000)
	//	{
	//	//	shape.setFillColor(sf::Color::Blue);
	//	}

		

		//moveBall();
	//}
















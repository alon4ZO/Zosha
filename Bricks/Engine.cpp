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

extern sf::RenderWindow * pWindow; //ALONB - temp..



void Engine::init(BasicObjects * xi_pObjects) {

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
	std::thread t1(&Engine::gameThread, Engine(), xi_pObjects);



	pWindow->display();

	while (pWindow->isOpen())
	{

		sf::Event event;
		while (pWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				pWindow->close();
		}
	}
}


void Engine::gameThread(BasicObjects * xi_pObjects) {
	while (1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		//cout << "It" << endl;
		if (GetKeyState('A') & 0x8000)
		{
			// Do stuff
		//	xi_pObjects->getrefreshList();
		//	xi_pObjects->moveFunc()();
		}
		else if (GetKeyState('B') & 0x8000)
		{
		//	shape.setFillColor(sf::Color::Blue);
		}

		//moveBall();
	}
}















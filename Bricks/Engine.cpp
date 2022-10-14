#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <windows.h>  
#include<thread>
#include "Display.h"
#include "BasicObjects.h"
#include "Engine.h"
using namespace std;

extern sf::RenderWindow * pWindow; //ALONB - temp..

extern sf::CircleShape * circle;

void Engine::init(BasicObjects * xi_objects) {

	std::list<combinedObjGeneric*> list = xi_objects->getrefreshList();

	for (std::list<combinedObjGeneric*>::iterator listIt = list.begin(); listIt != list.end(); listIt++)
	{
		std::list<basicObjectCommon *> shapeList = (*listIt)->getShapeList();
		cout << "Size" << shapeList.size() << endl;
		for (std::list<basicObjectCommon*>::iterator listShapesInComplexObject = shapeList.begin(); listShapesInComplexObject != shapeList.end(); listShapesInComplexObject++)
		{
			cout << "Loading Shape" << endl;
		    sf::Shape * s = (*listShapesInComplexObject)->getShape();
			xi_objects->getDrawFunction()(s);
		}
	}
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





//std::cout << sf::VideoMode::getDesktopMode().width << ", " << sf::VideoMode::getDesktopMode().height;








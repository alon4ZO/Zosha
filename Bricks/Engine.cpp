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

int usSinceLastRender =3000;

void Engine::init(BasicObjects *xi_pBasicObjects, Display * display)
{
	xi_pBasicObjects->drawAllBasicShapes();
	display->display();

	pWindow = display->getWindow();
	pWindow->setActive(false);

	sf::Clock clock;
	clock.restart().asMicroseconds(); // restart gives the amount of time passed and also restarts the clock allowing a constant looping

	while (pWindow->isOpen()) {
		sf::Event event; //why do i have to poll the event?

		xi_pBasicObjects->timeSinceLastStepUS = (int)clock.getElapsedTime().asMicroseconds();
		clock.restart().asMicroseconds(); // restart gives the amount of time passed and also restarts the clock allowing a constant looping

		pWindow->pollEvent(event);

		if (GetKeyState(VK_LEFT) & 0x8000) {
			xi_pBasicObjects->movePaddleLeft();
		}

		else if (GetKeyState(VK_RIGHT) & 0x8000) {
			xi_pBasicObjects->movePaddleRight();
		}

		else if (GetKeyState(VK_SPACE) & 0x8000) { //ALONB - only in debug.
			xi_pBasicObjects->reset();
		}




		xi_pBasicObjects->moveBall();

		pWindow->clear();
		xi_pBasicObjects->drawAllBasicShapes();
		display->display();
	}
}















//void Engine::gameThread(Animate * xi_pAnimate, Display * display) {
//	pWindow->setActive(true);
//
//}

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
















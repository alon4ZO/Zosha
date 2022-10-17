#include <iostream>
#include "Display.h"
#include <new>
#include <SFML/Graphics.hpp>



using namespace std;


void Display::init() {
	cout << "Initializing display" << endl;
	Display::screenSize.x = sf::VideoMode::getDesktopMode().width; 
	Display::screenSize.y = sf::VideoMode::getDesktopMode().height;
	screenSize.x *= SCREEN_DISPLAY_RATIO;
	screenSize.y *= SCREEN_DISPLAY_RATIO;
	//pWindow = new sf::RenderWindow(sf::VideoMode(Display::screenSize.x/2, Display::screenSize.y/2), "Bricks!", sf::Style::Fullscreen);
	pWindow = new sf::RenderWindow(sf::VideoMode(Display::screenSize.x, Display::screenSize.y), "Bricks!");
	pWindow->clear();
}

sf::Vector2i Display::getScreenSize()
{
	return Display::screenSize;	
}


void Display::drawShape(sf::Shape * xi_pShape)
{
	pWindow->draw(*xi_pShape);
}


void Display::moveShape(sf::Shape * xi_pShape)
{
	pWindow->draw(*xi_pShape);
}




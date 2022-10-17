#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <windows.h>  
#include<thread>
#include "Display.h"
#include "BasicObjects.h"
#include "Engine.h"
#include "Animate.h"
using namespace std;


int main()
{
	Display display;
	Engine engine;
	Animate Animate;

	display.init();

	Animate.registerDrawFunction([&display](sf::Shape* xi_pShape) -> void { return display.drawShape(xi_pShape); });
	Animate.registerMoveFunction([&display](sf::Shape* xi_pShape) -> void { return display.moveShape(xi_pShape); });

	Animate.init(display.getScreenSize());
	engine.init(&Animate, &display);
	return 0;
}





//sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML wgorks!");
//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML wgorks!", sf::Style::Fullscreen);
//sf::CircleShape shape(100.f);
//shape.setFillColor(sf::Color::Green);
//cout << "Hello";

////std::cout << sf::VideoMode::getDesktopMode().width << ", " << sf::VideoMode::getDesktopMode().height;


//while (window.isOpen())
//{
//	if (GetKeyState('A') & 0x8000)
//	{
//		// Do stuff
//		shape.setFillColor(sf::Color::Red);
//	}
//	else if (GetKeyState('B') & 0x8000)
//	{
//		shape.setFillColor(sf::Color::Blue);
//	}
//	else
//	{
//		shape.setFillColor(sf::Color::Magenta);
//		shape.setScale(0.5, 0.5);
//	}

//	window.clear();
//	window.draw(shape);
//	window.display();

//	sf::Event event;
//	while (window.pollEvent(event))
//	{
//		if (event.type == sf::Event::Closed)
//			window.close();
//	}
//}

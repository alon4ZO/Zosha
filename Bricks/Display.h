#ifndef __DISPLAY__
#define __DISPLAY__
#include <SFML/Graphics.hpp>



class Display
{
	sf::Vector2i screenSize;
	sf::Vector2i playSize;
	sf::RenderWindow window;


	public: 
		Display() {};
		void init();
		sf::Vector2i getScreenSize();
		void drawShape(sf::Shape * xi_shape);
		//void addShapeToWindow(Shape objects); TODO ALONB
};

#endif __DISPLAY__
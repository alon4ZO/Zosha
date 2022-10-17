#ifndef __DISPLAY__
#define __DISPLAY__
#include <SFML/Graphics.hpp>

#define SCREEN_DISPLAY_RATIO (0.9)

class Display
{
	sf::Vector2i screenSize;
	sf::Vector2i playSize;
	sf::RenderWindow * pWindow;


	public: 
		Display() {};
		void init();
		sf::Vector2i getScreenSize();
		void drawShape(sf::Shape * xi_shape);
		void moveShape(sf::Shape * xi_shape);
		void display() { pWindow->display(); }
		void clear() { pWindow->clear(); }
		sf::RenderWindow * getWindow() { return pWindow; } //ALONB - remove.
		//void addShapeToWindow(Shape objects); TODO ALONB
};

#endif __DISPLAY__
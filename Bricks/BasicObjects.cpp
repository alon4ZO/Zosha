#include "BasicObjects.h"
#include <iostream> 
#include <new>       
#include <list>       
#include "Display.h" //ALONB - what is the difference between .h and .hpp?
using namespace std;


sf::CircleShape * circle; //ALONB - why need to define this variable and not do it directly?
extern sf::RenderWindow * pWindow; //ALONB - temp..

void BasicObjects::init(sf::Vector2i xi_screenSize)
{
	//sf::Vector2i center(xi_screenSize.x / 2, xi_screenSize.y / 2);
	sf::Vector2f center(1, 0);
	sf::Vector2i speed(0,0);
	float radius = 100;
	ballObj.main.setCircleCharacteristics(&ballObj.mainShape, center, speed, radius);
	ballObj.addBasicShape(&ballObj.main);
	changeList.push_front(&ballObj);

	center = {100,0};
	speed = { 0,0 };
	sf::Vector2f dimensions(100, 100);
	paddleObj.main.setRectangleCharacteristics(&paddleObj.mainShape, center, speed, dimensions);
	paddleObj.addBasicShape(&paddleObj.main);
	changeList.push_front(&paddleObj);


	center = { 800, 100 };
	wallObj.ceiling.setRectangleCharacteristics(&wallObj.celingShape, center, speed, dimensions);
	center = { 300,0 };

	wallObj.left.setRectangleCharacteristics(&wallObj.leftShape, center, speed, dimensions);
	center = { 500,0 };

	wallObj.right.setRectangleCharacteristics(&wallObj.rightShape, center, speed, dimensions);

	wallObj.addBasicShape(&wallObj.ceiling);
	wallObj.addBasicShape(&wallObj.left);
	wallObj.addBasicShape(&wallObj.right);
	changeList.push_front(&wallObj);
}


void basicObjectCommon::setCircleCharacteristics(sf::CircleShape* xi_pShape, sf::Vector2f xi_centerLocation, sf::Vector2i xi_speed, float xi_radius) { //TODO: ADD COLOR
	centerLocation = xi_centerLocation;
	speed = xi_speed;
	radius = xi_radius;
	cout << "set c" << endl;
	xi_pShape->setPosition(0, 150);
	xi_pShape->setRadius(100.f);
	xi_pShape->setFillColor(sf::Color::Red);
	pShape = xi_pShape;


}

void basicObjectCommon::setRectangleCharacteristics(sf::RectangleShape* xi_pShape, sf::Vector2f xi_centerLocation, sf::Vector2i xi_speed, sf::Vector2f xi_dimensions) {
	centerLocation = xi_centerLocation;
	speed = xi_speed;
	dimensions = xi_dimensions;
	sf::RectangleShape * rectangle;
	xi_pShape->setSize(xi_dimensions);
	xi_pShape->setPosition(xi_centerLocation);
	xi_pShape->setFillColor(sf::Color::Blue);
	pShape = xi_pShape;

}
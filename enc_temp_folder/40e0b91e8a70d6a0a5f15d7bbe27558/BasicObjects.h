#ifndef __BASIC_OBJECTS__
#define __BASIC_OBJECTS__

#include <SFML/Graphics.hpp>
#include <list>
#include <functional>


#define NUM_OF_WALLS (3)


class basicObjectCommon
{
	sf::Vector2f centerLocation;
	sf::Vector2f dimensions;
	sf::Vector2i speed;
	sf::Shape * pShape; 
	float radius;
	int color;

public:
	void setCircleCharacteristics(sf::CircleShape*   , sf::Vector2f xi_centerLocation, sf::Vector2i xi_speed, float xi_radius );
	void setRectangleCharacteristics(sf::RectangleShape*, sf::Vector2f xi_centerLocation, sf::Vector2i xi_speed, sf::Vector2f xi_dimensions ); //ALONB - why can't i overload these 2 functions? It keeps on selecting the wrong 1?
	//void setCharacteristics(sf::RectangleShape*, sf::Vector2i xi_centerLocation, sf::Vector2i xi_speed, sf::Vector2f xi_dimensions ); //ALONB - why can't i overload these 2 functions? It keeps on selecting the wrong 1?
	sf::Shape * getShape() { return pShape; };
};



class combinedObjGeneric
{
protected:
	bool isRefreshRequired;
	std::list<basicObjectCommon *> shapeList;
public:
	void addBasicShape(basicObjectCommon * basicObjectCommon) { shapeList.push_front(basicObjectCommon); }
	std::list<basicObjectCommon *> getShapeList() { return shapeList; }
};



class ballObjC : public combinedObjGeneric {
public: //why public?
	basicObjectCommon main;
	sf::CircleShape mainShape;
};

class paddleObjC : public combinedObjGeneric {
public:
	basicObjectCommon main;
	sf::RectangleShape mainShape;
};

class WallObjC : public combinedObjGeneric {
public:
	basicObjectCommon left;
	basicObjectCommon right;
	basicObjectCommon ceiling;
	sf::RectangleShape leftShape;
	sf::RectangleShape rightShape;
	sf::RectangleShape celingShape;
};


class BasicObjects
{
	ballObjC ballObj;
	paddleObjC paddleObj; 
	WallObjC wallObj;

	std::list<combinedObjGeneric*> changeList;
	std::function<void(sf::Shape *)> drawFunc;


public:
	BasicObjects() {};
	void init(sf::Vector2i screenSize);
	void registerDisplayFunctions(std::function<void(sf::Shape *)> xi_function) { drawFunc = xi_function; }
	std::function<void(sf::Shape *)> getDrawFunction() { return drawFunc; }
	std::list<combinedObjGeneric*> getObjectsList() { return changeList; }
};


#endif __BASIC_OBJECTS__


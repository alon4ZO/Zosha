#ifndef __BASIC_OBJECTS__
#define __BASIC_OBJECTS__

#include <SFML/Graphics.hpp>
#include <list>
#include <functional>


#define GAME_OBJECTS_WALL_COLOR   (sf::Color::Magenta)
#define GAME_OBJECTS_BALL_COLOR   (sf::Color::Red)
#define GAME_OBJECTS_PADDLE_COLOR (sf::Color::Cyan)


#define GAME_OBJECTS_WALL_THIKNESS_RATIO (0.03) 
#define GAME_OBJECTS_WALL_HEIGHT_RATIO (0.9)
#define GAME_OBJECTS_WALL_WIDTH_RATIO (0.7)


#define GAME_OBJECTS_PADDLE_VERTICAL_THICKNESS_RATIO (0.02)
#define GAME_OBJECTS_PADDLE_VERTICAL_HEIGHT (0.91)
#define GAME_OBJECTS_PADDLE_WIDTH_RATIO (0.1)

class basicObjectCommon
{
	//sf::Vector2f centerLocation;
	//sf::Vector2f dimensions;
	sf::Vector2i speed;
	//float radius;
	int color;

	sf::Shape * pShape; 

public:
	void setCircleCharacteristics(sf::CircleShape*   , sf::Vector2f xi_centerLocation, sf::Vector2i xi_speed, float xi_radius, sf::Color xi_color);
	void setRectangleCharacteristics(sf::RectangleShape*, sf::Vector2f xi_centerLocation, sf::Vector2i xi_speed, sf::Vector2f xi_dimensions, sf::Color xi_color); //ALONB - why can't i overload these 2 functions? It keeps on selecting the wrong 1?
	//void setCharacteristics(sf::RectangleShape*, sf::Vector2i xi_centerLocation, sf::Vector2i xi_speed, sf::Vector2f xi_dimensions ); //ALONB - why can't i overload these 2 functions? It keeps on selecting the wrong 1?
	sf::Shape * getShape() { return pShape; };
};


class combinedObjGeneric
{
protected:
	std::list<basicObjectCommon *> shapeList;
public:
	void addBasicShape(basicObjectCommon * basicObjectCommon) { shapeList.push_front(basicObjectCommon); }
	std::list<basicObjectCommon *> getShapeList() { return shapeList; }
};


class ballObjC : public combinedObjGeneric {
public:
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
//public:
	ballObjC ballObj;
	paddleObjC paddleObj; 
	WallObjC wallObj;

	std::function<void(sf::Shape *)> drawFunc;
	void loadAllObjectShapes(combinedObjGeneric * xi_object);


public:
	void init(sf::Vector2i screenSize);

	void registerDisplayFunctions(std::function<void(sf::Shape *)> xi_function) { drawFunc = xi_function; }
	std::function<void(sf::Shape *)> getDrawFunction() { return drawFunc; }



	//void movePaddleLeft();
	//void movePaddleRight() {}
	//void moveBall() {}
};


#endif __BASIC_OBJECTS__


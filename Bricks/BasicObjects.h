#ifndef __BASIC_OBJECTS__
#define __BASIC_OBJECTS__

#include <SFML/Graphics.hpp>
#include <list>
#include <functional>

//Colors:
#define GAME_OBJECTS_GAME_WIN_COLOR                      (sf::Color::Black)
#define GAME_OBJECTS_GAME_WIN_FRAME_COLOR                (sf::Color::Magenta)
#define GAME_OBJECTS_BALL_COLOR                          (sf::Color::Red)
#define GAME_OBJECTS_PADDLE_COLOR		                 (sf::Color::Blue)

//Dimensions:
#define GAME_OBJECTS_GAME_WIN_FRAME_THIKNESS_RATIO       (0.03) //TO Y AXIS
#define GAME_OBJECTS_GAME_WIN_HEIGHT_RATIO               (0.9)
#define GAME_OBJECTS_GAME_WIN_WIDTH_RATIO                (0.65)

#define GAME_OBJECTS_PADDLE_VERTICAL_THICKNESS_RATIO     (0.03)
#define GAME_OBJECTS_PADDLE_VERTICAL_HEIGHT              (0.93)
#define GAME_OBJECTS_PADDLE_WIDTH_RATIO                  (0.125) //Length

#define GAME_OBJECTS_BALL_RADIUS_RATIO                   (0.025)

//Speed:
#define GAME_OBJECTS_PADDLE_REGULAR_SPEED                (7) //ALONB - change to ratios.
#define GAME_OBJECTS_BALL_DEFAULT_SPEED_X                (1)
#define GAME_OBJECTS_BALL_DEFAULT_SPEED_Y                (1)


class basicObjectCommon
{	//int color;
	sf::Shape * pShape; 

public:
	void setCircleCharacteristics(sf::CircleShape* xi_pShape, sf::Vector2f xi_centerLocation, float xi_radius, sf::Color xi_color);
	void setRectangleCharacteristics(sf::RectangleShape* xi_pShape, sf::Vector2f xi_centerLocation, sf::Vector2f xi_dimensions, sf::Color xi_color); //ALONB - why can't i overload these 2 functions? It keeps on selecting the wrong 1?
	//void setCharacteristics(sf::RectangleShape*, sf::Vector2i xi_centerLocation, sf::Vector2i xi_speed, sf::Vector2f xi_dimensions ); //ALONB - why can't i overload these 2 functions? It keeps on selecting the wrong 1?
	sf::Shape * getShape() { return pShape; };
};


class combinedObjGeneric
{
protected:
	std::list<basicObjectCommon *> shapeList;
public:
	void addBasicShape(basicObjectCommon * basicObjectCommon) { shapeList.push_back(basicObjectCommon); }
	std::list<basicObjectCommon *> getShapeList() { return shapeList; }
	sf::Vector2f speed;
	float farthestRightLocationOfFirstShape;
	float farthestLeftLocationOfFirstShape;

};


class ballObjC : public combinedObjGeneric {
public: //ALONB change this logic. It doensnt make sense that this is public.
	basicObjectCommon main;
	sf::CircleShape mainShape;

	float farthestRightLocationOfFirstShape;
	float farthestLeftLocationOfFirstShape;
	float farthestUpLocationOfFirstShape;
	float farthestDownLocationOfFirstShape;

};

class paddleObjC : public combinedObjGeneric {
public:
	basicObjectCommon main;
	sf::RectangleShape mainShape;
};

class GameWinObjC : public combinedObjGeneric {
public:
	basicObjectCommon center;
	basicObjectCommon outer;
	sf::RectangleShape centerShape;
	sf::RectangleShape outerShape;
};


class BasicObjects
{
protected:
	ballObjC ballObj;
	paddleObjC paddleObj; 
	GameWinObjC wallObj;
	std::list<combinedObjGeneric*>allGamePieces;

public:
	void init(sf::Vector2i screenSize);
};


#endif __BASIC_OBJECTS__


#ifndef __BASIC_OBJECTS__
#define __BASIC_OBJECTS__

#include <SFML/Graphics.hpp>
#include <list>
#include <functional>


enum SHAPES_FOR_OBJECT_BALL_E {
	SHAPES_FOR_OBJECT_BALL_MAIN,

	SHAPES_FOR_OBJECT_BALL_LAST
};

enum SHAPES_FOR_OBJECT_GAME_FRAME_E {
	SHAPES_FOR_OBJECT_GAME_FRAME_INNER,
	SHAPES_FOR_OBJECT_GAME_FRAME_OUTER,

	SHAPES_FOR_OBJECT_GAME_FRAME_LAST
};

enum SHAPES_FOR_OBJECT_PADDLE_E {
	SHAPES_FOR_OBJECT_PADDLE_BODY,

	SHAPES_FOR_OBJECT_PADDLE_LAST
};



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
#define GAME_OBJECTS_BALL_DEFAULT_SPEED_X                (2)
#define GAME_OBJECTS_BALL_DEFAULT_SPEED_Y                (-1)


class virtualObject
{
protected:
	std::list<sf::RectangleShape> rectangleShapesList;
	std::list<sf::CircleShape> circleShapesList;
	std::list<sf::Shape*> shapesList;
	sf::Vector2f speed;
	sf::Vector2f virtualDimensions; // virtural dimentions of all the combined shapes. //ALONB - union + indicator for these 2?
	float virtualRadius; // virtural dimentions of all the combined shapes.
	sf::Vector2f virtualLocation;

	float motionLimitLeft;
	float motionLimitRight;
	float motionLimitUp;
	float motionLimitBottom;

public:
//	void addBasicShape(sf::Shape * xi_shape) { shapeList.push_back(xi_shape); }
	auto getShapeList() { return shapesList; }

	void addCircleShape(float xi_radius, sf::Color xi_color, sf::Vector2f xi_offsetFromVirtualLocation, sf::Vector2f xi_speed);
	void addRectangleShape(sf::Vector2f xi_dimensions, sf::Color xi_color, sf::Vector2f xi_offsetFromVirtualLocation, sf::Vector2f xi_speed); //ALONB - why can't i overload these 2 functions? It keeps on selecting the wrong 1?
	

	sf::Vector2f getVirtualDimensions()					             { return virtualDimensions; }
	sf::Vector2f getVirtualLocation()					             { return virtualLocation;  }
	sf::Vector2f getSpeed()								             { return speed;  }
	float        getMotionLimitLeft()					             { return motionLimitLeft;  }
	float        getMotionLimitRight()					             { return motionLimitRight;  }
	float        getMotionLimitUp()						             { return motionLimitUp;  }
	float        getMotionLimitBottom()					             { return motionLimitBottom;  }


	void         setMotionLimitLeft(float xi_val)                    { motionLimitLeft = xi_val;  }
	void         setMotionLimitRight(float xi_val)                   { motionLimitRight = xi_val;  }
	void         setMotionLimitTop(float xi_val)                      { motionLimitUp = xi_val;  }
	void         setMotionLimitBottom(float xi_val)                  { motionLimitBottom = xi_val; }
	void setVirtualDimensions(sf::Vector2f x_virtualDimensions)      { virtualDimensions = x_virtualDimensions; }
	void setVirtualLocation(sf::Vector2f x_virtualLocation)          { virtualLocation = x_virtualLocation; }
	void setSpeed(sf::Vector2f xi_speed )                            { speed = xi_speed; }
	
	void loadShapesToAbstractShapeList();
	void moveStep();								



};

class BasicObjects : public virtualObject
{
protected:
	virtualObject ballObj;
	virtualObject paddleObj;
	virtualObject gameFrame;
	std::list<virtualObject*>allGamePieces;

	std::function<void(sf::Shape *)> drawFunc;
	std::function<void(sf::Shape *)> moveFunc;

public:
	void init(sf::Vector2i screenSize);
	void registerDrawFunction(std::function<void(sf::Shape *)> xi_function) { drawFunc = xi_function; }
	void registerMoveFunction(std::function<void(sf::Shape *)> xi_function) { moveFunc = xi_function; }
	void drawAllBasicShapes();
	void movePaddleLeft();
	void movePaddleRight();
	void moveBall();

	//auto getAllGamePieces() { return allGamePieces; }
};


#endif __BASIC_OBJECTS__



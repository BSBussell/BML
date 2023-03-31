
// Bee Bussell
// Sept 6, 2021
// Creating Rectangles and more

/*
	Might seem pointless but eventually I plan on baking methods into these
*/

#ifndef BML_RECT_H
#define BML_RECT_H

#include <SDL2/SDL.h>
#include <cstdint>
 

// Forward declarations
struct bPoint;
struct bPointF;
struct bRect;
struct bRectF;

// @brief Integer, can be used as a vector2d

struct bPoint {

	Uint32 x, y;

	// Normalize the point
	void normalize();

	// Easy conversion to SDL_Point
	operator SDL_Point() const;

	// Conversion to bPointF
    operator bPointF() const;


	// ###### Math Operators ######
	// ###########################

	// the + and - operators with bPoint
    bPoint operator+(const bPoint& other) const;
    bPoint operator-(const bPoint& other) const;

	// the * and / operators with a scalar
    bPoint operator*(Uint32 scalar) const;
    bPoint operator/(Uint32 scalar) const;


	// ###### Assignment Operators ######
	// #################################

	// += and -= operators with bPoint
	bPoint operator+=(const bPoint& other);
	bPoint operator-=(const bPoint& other);

	// *= and /= operators with a scalar
	bPoint operator*=(Uint32 scalar);
	bPoint operator/=(Uint32 scalar);
};


/**
 * @brief A struct for holding a 2D rectangle
 * 
 */
struct bPointF {

	float x, y;

	// Normalize the vector
	void normalize();

	float length() const {
		return sqrt(x * x + y * y);
	}

	// Conversion to bPoint
    operator bPoint() const;

	// ###### Math Operators ######
	// ###########################

    // + and - operators with bPointF
    bPointF operator+(const bPointF& other) const;
    bPointF operator-(const bPointF& other) const;

    // * and / operators with a scalar
    bPointF operator*(float scalar) const;
    bPointF operator/(float scalar) const;

	// ###### Assignment Operators ######
	// #################################

	// += and -= operators with bPointF
	bPointF operator+=(const bPointF& other);
	bPointF operator-=(const bPointF& other);

	// *= and /= operators with a scalar
	bPointF operator*=(float scalar);
	bPointF operator/=(float scalar);
};



struct bRect {

	Uint32 x;
	Uint32 y;
	Uint32 width;
	Uint32 height;


	// Return the center of the rectangle
	bPoint center() const;

	// Checks if the two rectangles intersect
	bool intersects(const bRect& other);

	// Easy conversion to SDL_Rect
    operator SDL_Rect() const;

	operator bRectF() const;

	// ###### Math Operators ########
	// ##############################

	// Adding and subtracting with a bRect
	bRect operator+(const bRect &other) const;
	bRect operator-(const bRect &other) const;

	// Multiplying and dividing with a scalar
	bRect operator*(Uint32 scalar) const;
	bRect operator/(Uint32 scalar) const;

	// ###### Assignment Operators ########
	// ####################################

	// += and -= with a bRect
	bRect& operator+=(const bRect &other);
	bRect& operator-=(const bRect &other);

	// += and -= with a bPoint
	bRect &operator+=(const bPoint &other);
	bRect &operator-=(const bPoint &other);

	// *= and /= with a scalar
	bRect& operator*=(Uint32 scalar);
	bRect& operator/=(Uint32 scalar);

};

struct bRectF {

	float x, y;
	float width, height;

	// Return the center of the rectangle
	bPointF center() const;

	// Return the intersection of two rectangles
	bRectF intersection(const bRectF& other) const;

	// Checks if the two rectangles intersect
	bool intersects(const bRectF& other);

	// Conversion to bRect
	operator bRect() const;


	// ###### Math Operators ########
	// ##############################

	// +, and - with a bRectF
	bRectF operator+(const bRectF& other) const;
    bRectF operator-(const bRectF& other) const;

	// *, and / with a scalar
    bRectF operator*(float scalar) const;
    bRectF operator/(float scalar) const;

	// +, -, *, and / with a bPointF
	bRectF& operator+(const bPointF& other);
	bRectF& operator-(const bPointF& other);
	bRectF& operator*(const bPointF& other);
	bRectF& operator/(const bPointF& other);

	// ###### Assignment Operators ########
	// ####################################

	// += and -= with a bRect
    bRectF& operator+=(const bRectF& other);
    bRectF& operator-=(const bRectF& other);

	// *= and /= with a scalar
    bRectF& operator*=(float scalar);
    bRectF& operator/=(float scalar);

	// +=, -=, *=, and /= with a bPointF
	bRectF& operator+=(const bPointF& other);
	bRectF& operator-=(const bPointF& other);
	bRectF& operator*=(const bPointF& other);
	bRectF& operator/=(const bPointF& other);



};

float dot_product(const bPointF& a, const bPointF& b);

#endif

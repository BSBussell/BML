
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

	// @brief Fixed-point addition
    bPoint operator+(const bPoint& other) const {
        return {x + other.x, y + other.y};
    }

    // @brief
    bPoint operator-(const bPoint& other) const {
        return {x - other.x, y - other.y};
    }

    // @brief Fixed-point multiplication by scalar
    bPoint operator*(Uint32 scalar) const {
        return {x * scalar, y * scalar};
    }

    // @brief Fixed-point division by scalar
    bPoint operator/(Uint32 scalar) const {
        return {x / scalar, y / scalar};
    }

	// @brief the += operator
	bPoint operator+=(const bPoint& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	bPoint operator-=(const bPoint& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	bPoint operator*=(Uint32 scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	bPoint operator/=(Uint32 scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
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

    // @brief Fixed-point addition
    bPointF operator+(const bPointF& other) const {
        return {x + other.x, y + other.y};
    }

    // @brief Fixed-point subtraction
    bPointF operator-(const bPointF& other) const {
        return {x - other.x, y - other.y};
    }

    // @brief Fixed-point multiplication by scalar
    bPointF operator*(float scalar) const {
        return { (x * scalar), (y * scalar)};
    }

    // @brief Fixed-point division by scalar
    bPointF operator/(float scalar) const {
        return {(x / scalar), (y / scalar)};
    }
	
	// @brief the += operator
	bPointF operator+=(const bPointF& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	bPointF operator-=(const bPointF& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	bPointF operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	bPointF operator/=(float scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
};



struct bRect {

	Uint32 x;
	Uint32 y;
	Uint32 width;
	Uint32 height;


	// Return the center of the rectangle
	bPoint center() const;

	float left() const { return x; }
    float right() const { return x + width; }
    float top() const { return y; }
    float bottom() const { return y + height; }

	// Checks if the two rectangles intersect
	bool intersects(const bRect& other);

	// Easy conversion to SDL_Rect
    operator SDL_Rect() const;

	operator bRectF() const;

	// Math Operators
	bRect operator+(const bRect &other) const {
		return {x + other.x, y + other.y, width + other.width, height + other.height};
	}

	bRect operator-(const bRect &other) const {
		return {x - other.x, y - other.y, width - other.width, height - other.height};
	}

	bRect operator*(Uint32 scalar) const {
		return {x * scalar, y * scalar, width * scalar, height * scalar};
	}

	bRect operator/(Uint32 scalar) const {
		return {x / scalar, y / scalar, width / scalar, height / scalar};
	}

	bRect& operator+=(const bRect &other) {
		x += other.x;
		y += other.y;
		width += other.width;
		height += other.height;
		return *this;
	}

	bRect& operator-=(const bRect &other) {
		x -= other.x;
		y -= other.y;
		width -= other.width;
		height -= other.height;
		return *this;
	}

	bRect& operator*=(Uint32 scalar) {
		x *= scalar;
		y *= scalar;
		width *= scalar;
		height *= scalar;
		return *this;
	}

	bRect& operator/=(Uint32 scalar) {
		x /= scalar;
		y /= scalar;
		width /= scalar;
		height /= scalar;
		return *this;
	}

};

struct bRectF {

	float x, y;
	float width, height;

	// Return the center of the rectangle
	bPointF center() const;

	// Return the intersection of two rectangles
	bRectF intersection(const bRectF& other) const {


		float x1 = fmax(x, other.x);
		float y1 = fmax(y, other.y);
		float x2 = fmin(x + width, other.x + other.width);
		float y2 = fmin(y + height, other.y + other.height);

		return {x1, y1, x2 - x1, y2 - y1};
	}

	// Checks if the two rectangles intersect
	bool intersects(const bRectF& other);

	operator bRect() const;

	// Math Operators
	bRectF operator+(const bRectF& other) const {
        return {x + other.x, y + other.y, width + other.width, height + other.height};
    }

    bRectF operator-(const bRectF& other) const {
        return {x - other.x, y - other.y, width - other.width, height - other.height};
    }

    bRectF operator*(float scalar) const {
        return {x * scalar, y * scalar, width * scalar, height * scalar};
    }

    bRectF operator/(float scalar) const {
        return {x / scalar, y / scalar, width / scalar, height / scalar};
    }

    bRectF& operator+=(const bRectF& other) {
        x += other.x;
        y += other.y;
        width += other.width;
        height += other.height;
        return *this;
    }

    bRectF& operator-=(const bRectF& other) {
        x -= other.x;
        y -= other.y;
        width -= other.width;
        height -= other.height;
        return *this;
    }

    bRectF& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        width *= scalar;
        height *= scalar;
        return *this;
    }

    bRectF& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        width /= scalar;
        height /= scalar;
        return *this;
    }

	// Point Operators
	bRectF& operator+(const bPointF& other) {
		x += other.x;
		y += other.y;
		return *this;
		
	}

	bRectF& operator-(const bPointF& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	bRectF& operator*(const bPointF& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	bRectF& operator/(const bPointF& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	bRectF& operator+=(const bPointF& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	bRectF& operator-=(const bPointF& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	bRectF& operator*=(const bPointF& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	bRectF& operator/=(const bPointF& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

};

float dot_product(const bPointF& a, const bPointF& b);

#endif

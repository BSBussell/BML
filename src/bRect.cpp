// Bee Bussell
// Sept 7, 2021
// Conversion functions


#include "bRect.h"

// ###############################
// ###### bPoint functions #######

void bPoint::normalize() {

    float mag = sqrt(x * x + y * y);
    x /= mag;
    y /= mag;
}

bPoint::operator SDL_Point() const {

	SDL_Point point;
	point.x = static_cast<int>(x);
    point.y = static_cast<int>(y);
	return point;
}

// Conversion to bPointF
bPoint::operator bPointF() const {
    return {static_cast<float>(x), static_cast<float>(y)};
}

// ###############################
// ###### bPointF functions ######

void bPointF::normalize() {

    float mag = sqrt(x * x + y * y);
    x /= mag;
    y /= mag;
}

// Conversion to bPoint
bPointF::operator bPoint() const {

    // Adds 0.5 to round to nearest integer
    return {static_cast<Uint32>(x + 0.5f), static_cast<Uint32>(y + 0.5f)};
}

// ##############################
// ###### bRect functions #######

bPoint bRect::center() const {
    return {x + width / 2, y + height / 2};
}

bool bRect::intersects(const bRect &other) {

    if (x < other.x + other.width &&
        x + width > other.x &&
        y < other.y + other.height &&
        y + height > other.y) {
        return true;
    }
    return false;
}

bRect::operator SDL_Rect() const {

	SDL_Rect rect;
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
    rect.w = static_cast<int>(width);
    rect.h = static_cast<int>(height);
    return rect;

}

bRect::operator bRectF() const {
    return {static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)};
}

// ##############################
// ###### bRectF functions ######

bPointF bRectF::center() const {
    return {x + width / 2, y + height / 2};
}

bool bRectF::intersects(const bRectF &other) {

    if (x < other.x + other.width &&
        x + width > other.x &&
        y < other.y + other.height &&
        y + height > other.y) {
        return true;
    }
    return false;
}

bRectF::operator bRect() const {

    // Adds 0.5 to round to nearest integer
    return {static_cast<Uint32>(x + 0.5f), static_cast<Uint32>(y + 0.5f), static_cast<Uint32>(width + 0.5f), static_cast<Uint32>(height + 0.5f)};
}

float dot_product(const bPointF &a, const bPointF &b) {
    return a.x * b.x + a.y * b.y;
}
// Bee Bussell
// Sept 7, 2021
// Conversion functions


#include "bRect.h"

// ###### bPoint Methods #########
// ###############################
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

bPoint::operator bPointF() const {
    return {static_cast<float>(x), static_cast<float>(y)};
}

bPoint bPoint::operator+(const bPoint &other) const {
	return {x + other.x, y + other.y};
}

bPoint bPoint::operator-(const bPoint &other) const {
	return {x - other.x, y - other.y};
}

bPoint bPoint::operator*(Uint32 scalar) const {
	return {x * scalar, y * scalar};
}

bPoint bPoint::operator/(Uint32 scalar) const {
	return {x / scalar, y / scalar};
}

bPoint bPoint::operator+=(const bPoint &other) {
	x += other.x;
	y += other.y;
	return *this;
}

bPoint bPoint::operator-=(const bPoint &other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

bPoint bPoint::operator*=(Uint32 scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

bPoint bPoint::operator/=(Uint32 scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}

// ###### bPointF functions ######
// ###############################

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

bPointF bPointF::operator+(const bPointF &other) const {
	return {x + other.x, y + other.y};
}

bPointF bPointF::operator-(const bPointF &other) const {
	return {x - other.x, y - other.y};
}

bPointF bPointF::operator*(float scalar) const {
	return { (x * scalar), (y * scalar)};
}

bPointF bPointF::operator/(float scalar) const {
	return {(x / scalar), (y / scalar)};
}

bPointF bPointF::operator+=(const bPointF &other) {
	x += other.x;
	y += other.y;
	return *this;
}

bPointF bPointF::operator-=(const bPointF &other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

bPointF bPointF::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

bPointF bPointF::operator/=(float scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}


// ###### bRect functions #######
// ##############################

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

bRect bRect::operator+(const bRect &other) const {
	return {x + other.x, y + other.y, width + other.width, height + other.height};
}

bRect bRect::operator-(const bRect &other) const {
	return {x - other.x, y - other.y, width - other.width, height - other.height};
}

bRect bRect::operator*(Uint32 scalar) const {
	return {x * scalar, y * scalar, width * scalar, height * scalar};
}

bRect bRect::operator/(Uint32 scalar) const {
	return {x / scalar, y / scalar, width / scalar, height / scalar};
}

bRect &bRect::operator+=(const bRect &other) {
	x += other.x;
	y += other.y;
	width += other.width;
	height += other.height;
	return *this;
}

bRect &bRect::operator-=(const bRect &other) {
	x -= other.x;
	y -= other.y;
	width -= other.width;
	height -= other.height;
	return *this;
}

// @brief the += operator for bPoints
bRect &bRect::operator+=(const bPoint &other) {
	x += other.x;
	y += other.y;
	return *this;
}

// @brief the -= operator for bPoints
bRect &bRect::operator-=(const bPoint &other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

bRect &bRect::operator*=(Uint32 scalar) {
	x *= scalar;
	y *= scalar;
	width *= scalar;
	height *= scalar;
	return *this;
}

bRect &bRect::operator/=(Uint32 scalar) {
	x /= scalar;
	y /= scalar;
	width /= scalar;
	height /= scalar;
	return *this;
}







// ###### bRectF functions ######
// ##############################
bPointF bRectF::center() const {
    return {x + width / 2, y + height / 2};
}

bRectF bRectF::intersection(const bRectF &other) const {


	float x1 = fmax(x, other.x);
	float y1 = fmax(y, other.y);
	float x2 = fmin(x + width, other.x + other.width);
	float y2 = fmin(y + height, other.y + other.height);

	return {x1, y1, x2 - x1, y2 - y1};
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

bRectF bRectF::operator+(const bRectF &other) const {
	return {x + other.x, y + other.y, width + other.width, height + other.height};
}

bRectF bRectF::operator-(const bRectF &other) const {
	return {x - other.x, y - other.y, width - other.width, height - other.height};
}

bRectF bRectF::operator*(float scalar) const {
	return {x * scalar, y * scalar, width * scalar, height * scalar};
}

bRectF bRectF::operator/(float scalar) const {
	return {x / scalar, y / scalar, width / scalar, height / scalar};
}

bRectF &bRectF::operator+=(const bRectF &other) {
	x += other.x;
	y += other.y;
	width += other.width;
	height += other.height;
	return *this;
}

bRectF &bRectF::operator-=(const bRectF &other) {
	x -= other.x;
	y -= other.y;
	width -= other.width;
	height -= other.height;
	return *this;
}

bRectF &bRectF::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	width *= scalar;
	height *= scalar;
	return *this;
}

bRectF &bRectF::operator/=(float scalar) {
	x /= scalar;
	y /= scalar;
	width /= scalar;
	height /= scalar;
	return *this;
}

bRectF &bRectF::operator+=(const bPointF &other) {
	x += other.x;
	y += other.y;
	return *this;
}

bRectF &bRectF::operator-=(const bPointF &other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

bRectF &bRectF::operator*=(const bPointF &other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

bRectF &bRectF::operator/=(const bPointF &other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

bRectF &bRectF::operator+(const bPointF &other) {
	x += other.x;
	y += other.y;
	return *this;

}

bRectF &bRectF::operator-(const bPointF &other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

bRectF &bRectF::operator*(const bPointF &other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

bRectF &bRectF::operator/(const bPointF &other) {
	x /= other.x;
	y /= other.y;
	return *this;
}


float dot_product(const bPointF &a, const bPointF &b) {
    return a.x * b.x + a.y * b.y;
}
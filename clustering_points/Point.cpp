#include <math.h>
#include "Point.h"


Point::Point(double x, double y) : x(x), y(y)
{
}

Point::Point(const Point& other){
	x = other.x;
	y = other.y;
}

Point::~Point()
{
}

const double Point::getX() const{
	return x;
}

const double Point::getY() const{
	return y;
}

void Point::setX(double x){
	this->x = x;
}	

void Point::setY(double y){
	this->y = y;
}

bool Point::operator==(const Point& other) const {
	return (other.getX() == this->getX()) && (other.getY() == this->getY());
}

const double Point::getDistanceFrom(const Point& p){
	return sqrt(pow(p.getX() - getX(), 2) + pow(p.getY() - getY(), 2));
}

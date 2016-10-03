#include "MovingPoint.h"
#include <math.h>

int MovingPoint::NEXT_ID = 0;

MovingPoint::MovingPoint(double x, double y, double radius) : id(NEXT_ID++), Point(x, y), radius(radius)
{
}

MovingPoint::MovingPoint(const Point& point) : id(NEXT_ID++), Point(point), radius(0)
{
}

MovingPoint::MovingPoint(const Point& point, double radius) : id(NEXT_ID++), Point(point), radius(radius)
{
}

MovingPoint::MovingPoint(const MovingPoint& otherMovingPoint) : Point(otherMovingPoint)
{
	id = otherMovingPoint.id;
	radius = otherMovingPoint.radius;
}

MovingPoint::~MovingPoint()
{
}

double MovingPoint::getRadius() const{
	return radius;
}

void MovingPoint::setRadius(double radius){
	this->radius = radius;
}

bool MovingPoint::operator == (const Point& other) const{
	if (!(Point::operator == (other))){
		return false;
	}

	const MovingPoint* mp = dynamic_cast<const MovingPoint*> (&other);
	return radius == mp->getRadius();
}
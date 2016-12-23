#pragma once
#include "Point.h"
#include "EncodedMovingPoint.h"
#include <iostream>

using namespace std;

class MovingPoint : public Point
{
private:
	static int NEXT_ID;
	int id;
	double radius;

public:
	MovingPoint();
	MovingPoint(double x, double y, double radius);
	MovingPoint(const Point& point);
	MovingPoint(const Point& point, double radius);
	MovingPoint(const MovingPoint& point);
	MovingPoint(const ENCODED_MOVING_POINT& encoded_moving_point);
	~MovingPoint();

	double getRadius() const;
	void setRadius(double radius);

	virtual bool operator==(const Point& other) const;

	virtual void toOs(ostream& os) const {
		os << ", radius: " << radius;
	}
};


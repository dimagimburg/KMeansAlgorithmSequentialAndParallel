#pragma once
#include "Point.h"
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
	~MovingPoint();

	double getRadius() const;
	void setRadius(double radius);

	virtual bool operator==(const Point& other) const;

	friend ostream &operator<<(ostream& os, const MovingPoint& p){
		const Point& point = p;
		os << "[" << p.id << "] [moving point] " << point << ", radius: " << p.radius;
		return os;
	}
};


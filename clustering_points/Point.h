#pragma once
#include <iostream>

class Point
{
private:
	double x;
	double y;
public:
	Point(double x = 0.0, double y = 0.0);
	Point(const Point& other);
	virtual ~Point();

	const double getX() const;
	const double getY() const;
	void setX(double x);
	void setY(double y);

	const double getDistanceFrom(const Point& p);

	virtual bool operator==(const Point& other) const;
	virtual void toOs(std::ostream& os) const {};

	friend std::ostream& operator<<(std::ostream& os, const Point& p)
	{
		os << "x: " << p.x << ", y: " << p.y;
		p.toOs(os);
		return os;
	}
};

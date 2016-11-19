#pragma once
#include <vector>
#include <iostream>
#include "Point.h"
#include "MovingPoint.h"
using namespace std;

class Cluster
{
private:
	static int NEXT_ID;
	const int id;
	Point* center;
	vector<Point*> points;

public:
	Cluster();
	Cluster(Point* p);
	Cluster(const Point* p);
	~Cluster();

	void recenter();
	void addPoint(Point* p);
	void clear();
	void setCenter(Point* p);
	const Point* getCenter() const;
	vector<Point*>* getPoints();
	const size_t size() const;

	bool operator==(const Cluster& other) const;

	friend ostream& operator<<(ostream& os, const Cluster& c)
	{
		os << "=========================" << endl;
		os << "Cluster : " << c.id << endl;
		os << "center : " << *(c.center) << endl;
		os << "-------------------------" << endl;
		vector<Point*>::const_iterator  itr = c.points.begin();
		vector<Point*>::const_iterator  itrEnd = c.points.end();
		// TODO: make below depend on variable
		// UNCOMMENT BELOW TO SEE THE POINTS IN THE CLUSTER
		/*
		for (; itr != itrEnd; ++itr)
			os << "point: " << *(*itr) << endl;
		*/
		os << "=========================" << endl;
		return os;
	}
};
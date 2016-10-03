#include "Cluster.h"


int Cluster::NEXT_ID = 0;

Cluster::Cluster() : id(NEXT_ID++)
{
}

Cluster::Cluster(Point* p) : id(NEXT_ID++)
{
	center = Point(*p);
	this->addPoint(p);
}

Cluster::~Cluster()
{
}

void Cluster::addPoint(Point* p){
	if (points.size() == 0){
		center = Point(*p);
	}
	this->points.push_back(p);
}

void Cluster::clear(){
	this->points.clear();
}

void Cluster::setCenter(Point p){
	this->center = p;
}

Point Cluster::getCenter(){
	return this->center;
}

void Cluster::recenter(){
	double x = 0, y = 0;
	Point new_center;
	vector<Point*>::const_iterator itr = points.begin();
	vector<Point*>::const_iterator itrEnd = points.end();
	for (; itr != itrEnd; ++itr)
	{
		x += (*(*itr)).getX();
		y += (*(*itr)).getY();
	}
	new_center.setX(x / points.size());
	new_center.setY(y / points.size());
	center = new_center;
}

bool Cluster::operator==(const Cluster& other) const{
	Point new_center;
	vector<Point*>::const_iterator itr = points.begin();
	vector<Point*>::const_iterator itrEnd = points.end();

	return false;
}
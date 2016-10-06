#include "Cluster.h"


int Cluster::NEXT_ID = 0;

Cluster::Cluster() : id(NEXT_ID++)
{
}

Cluster::Cluster(Point* p) : id(NEXT_ID++)
{
	center = new Point(*p);
	//this->addPoint(p);
}

Cluster::Cluster(const Point* p) : id(NEXT_ID++)
{
	center = new Point(*p);
	//this->addPoint(p);
}

Cluster::~Cluster()
{
}

void Cluster::addPoint(Point* p){
	if (points.size() == 0 && center == NULL){
		center = p;
	}
	this->points.push_back(p);
}

void Cluster::clear(){
	this->points.clear();
}

void Cluster::setCenter(Point* p){
	this->center = p;
}

const Point* Cluster::getCenter() const{
	return this->center;
}

vector<Point*>* Cluster::getPoints(){
	return &this->points;
}

void Cluster::recenter(){
	double x = 0, y = 0;
	Point* new_center = new Point();
	vector<Point*>::const_iterator itr = points.begin();
	vector<Point*>::const_iterator itrEnd = points.end();
	for (; itr != itrEnd; ++itr)
	{
		x += (*(*itr)).getX();
		y += (*(*itr)).getY();
	}
	(*new_center).setX(x / points.size());
	(*new_center).setY(y / points.size());
	center = new_center;
}

const size_t Cluster::size() const {
	return this->points.size();
}

bool Cluster::operator==(const Cluster& other) const {
	vector<Point*>::const_iterator itr = points.begin();
	vector<Point*>::const_iterator itrEnd = points.end();

	if (other.size() != this->size() || !(*(other.getCenter()) == *(this->getCenter()))){
		return false;
	}

	for (; itr != itrEnd; ++itr)
	{
		bool found = false;
		vector<Point*>::const_iterator other_itr = other.points.begin();
		vector<Point*>::const_iterator other_itrEnd = other.points.end();
		for (; other_itr != other_itrEnd; ++other_itr){
			if ((*(*itr)) == (*(*other_itr))){
				found = true;
				break;
			}
		}
		if (!found) return false;
	}

	return true;
}
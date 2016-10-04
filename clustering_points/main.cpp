#include <iostream>
#include "Point.h"
#include "MovingPoint.h"
#include "Cluster.h"
#include "Config.h"
#include "Utils.h"
#include "SequentialKMeans.h"

using namespace std;

// TODO's
// 1. implement hard copy constructor for clusters

int main()
{
	Config config = Utils::createConfigFromFile("input.txt");
	vector<Point*> points = Utils::getMovingPointsFromFile("input.txt");

	SequentialKMeans s_kmeans(config, &points);
	vector<Cluster*> clusters = s_kmeans.getClusters(0);

	cout << *(clusters.at(0)) << endl;
	cout << *(clusters.at(1)) << endl;
	cout << *(clusters.at(2)) << endl;


	/*
	Point* p = new MovingPoint(1,1,2.1);
	Point* p2 = new Point(2,2);

	cout << *p << endl;

	Cluster* c = new Cluster(p);
	(*c).addPoint(p2);
	(*c).recenter();

	cout << *c << endl;
	*/
	//cout << config << "\n";

	//cout << points.at(0) << endl;
	//cout << points.at(1) << endl;
	//cout << points.at(2) << endl;
	//cout << points.at(3) << endl;
	//cout << points.at(4) << endl;
	//cout << points.at(5) << endl;
	//cout << points.at(6) << endl;
	//cout << points.at(7) << endl;
	//cout << points.at(8) << endl;
	//cout << points.at(9) << endl;

	//cout << (points.at(9) == points.at(10)) << endl;

	//SequentialKMeans s_kmeans(config, &points);
	//vector<Cluster*> clusters = s_kmeans.getClusters(0);

	//cout << *(clusters.at(0)) << endl;
	//cout << *(clusters.at(1)) << endl;
	//cout << *(clusters.at(2)) << endl;
}
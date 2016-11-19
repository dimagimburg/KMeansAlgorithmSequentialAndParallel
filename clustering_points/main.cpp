#include <iostream>
#include <mpi.h>
#include "Point.h"
#include "MovingPoint.h"
#include "Cluster.h"
#include "Config.h"
#include "Utils.h"
#include "SequentialKMeans.h"

using namespace std;

// TODO's
// 1. implement point movment in circle based on radius
int main()
{
	Config config = Utils::createConfigFromFile("test2.txt");
	ENCODED_MOVING_POINT* emp_vector = Utils::getEncodeMovingPointsFromFile("test2.txt");



	/*
	vector<Point*> points = Utils::getMovingPointsFromFile("test2.txt");

	SequentialKMeans s_kmeans(config, &points);
	vector<Cluster> clusters = s_kmeans.getClusters(0);

	cout << "************" << endl;
	cout << clusters.at(0) << endl;
	cout << clusters.at(1) << endl;
	cout << clusters.at(2) << endl;
	cout << clusters.at(3) << endl;
	*/

}
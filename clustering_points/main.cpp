#include <iostream>
#include "Point.h"
#include "MovingPoint.h"
#include "Cluster.h"
#include "Config.h"
#include "Utils.h"
#include "SequentialKMeans.h"

using namespace std;

int main()
{
	Config config = Utils::createConfigFromFile("input.txt");
	vector<Point*> points = Utils::getMovingPointsFromFile("input.txt");

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

	SequentialKMeans s_kmeans(config, &points);
	vector<Cluster*> clusters = s_kmeans.getClusters(0);

	cout << *(clusters.at(0)) << endl;
}
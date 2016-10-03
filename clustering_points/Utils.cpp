#include "Utils.h"
#include "MovingPoint.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>

using namespace std;

Utils::Utils()
{
}


Utils::~Utils()
{
}

Config Utils::createConfigFromFile(std::string filename){
	enum {
		TOTAL_POINTS_POS,
		N_CLUSTERS_POS,
		DELTA_T_POS,
		TIME_POS,
		LIMIT_POS
	};

	// store first config line string into config_line
	ifstream file(filename);
	string config_line;
	getline(file, config_line);

	// set the config tokens one by one into a vector
	vector<string> config_tokens;
	istringstream iss(config_line);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(config_tokens));

	int total_points = stoi(config_tokens.at(TOTAL_POINTS_POS));
	int n_clusters = stoi(config_tokens.at(N_CLUSTERS_POS));
	double delta_t = stod(config_tokens.at(DELTA_T_POS));
	double time = stod(config_tokens.at(TIME_POS));
	int limit = stoi(config_tokens.at(LIMIT_POS));

	return Config(total_points, n_clusters, delta_t, time, limit);
}

vector<Point*> Utils::getMovingPointsFromFile(std::string filename){
	enum {
		POINT_ID,
		POINT_X,
		POINT_Y,
		POINT_RADIUS
	};
	int id;
	double x, y, r;

	vector<Point*> points;

	ifstream file(filename);
	string point_line;

	getline(file, point_line); // first line is for config

	while (getline(file, point_line)){
		vector<string> point_tokens;
		istringstream iss(point_line);
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(point_tokens));

		x = stod(point_tokens.at(POINT_X));
		y = stod(point_tokens.at(POINT_Y));
		r = stod(point_tokens.at(POINT_RADIUS));

		points.push_back(new MovingPoint(x, y, r));
	}

	return points;
}

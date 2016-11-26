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

Config Utils::createConfigFromFile(char* filename){
	int total_points = 0;
	int n_clusters = 0;
	double delta_t = 0;
	double time = 0;
	int limit = 0;

	FILE* f;
	errno_t errorCode = fopen_s(&f, filename, "r");
	if (errorCode != 0)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	int row = fscanf_s(f, "%d %d %lf %lf %d", &total_points, &n_clusters, &delta_t, &time, &limit);
	fclose(f);

	return Config(total_points, n_clusters, delta_t, time, limit);
}

vector<Point*> Utils::getMovingPointsFromFile(char* filename){
	double x = 0.0, y = 0.0, r = 0.0;
	int index = 0;
	vector<Point*> points;
	FILE* f;

	errno_t errorCode = fopen_s(&f, filename, "r");
	if (errorCode != 0)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	// first line is config line - ignore (http://stackoverflow.com/a/16108311/2698072)
	int row = fscanf_s(f, "%*[^\n]\n", NULL); 

	// fscanf_s(f, "%d %lf %lf %lf\n", &index, &x, &y, &r) != EOF) read the last line twice (http://stackoverflow.com/a/26570818/2698072)
	// == 4 is the number of the parameters we read from line.
	while (fscanf_s(f, "%d %lf %lf %lf\n", &index, &x, &y, &r) == 4) { 
		points.push_back(new MovingPoint(x, y, r));
	}

	fclose(f);

	return points;
}

ENCODED_MOVING_POINT* Utils::getEncodeMovingPointsFromFile(char* filename){
	enum {
		POINT_ID,
		POINT_X,
		POINT_Y,
		POINT_RADIUS
	};

	Config config = createConfigFromFile(filename);

	ENCODED_MOVING_POINT* emp_vector = (ENCODED_MOVING_POINT*) malloc(config.getTotalPoints() * sizeof(ENCODED_MOVING_POINT));

	ifstream file(filename);
	string point_line;

	getline(file, point_line); // first line is for config

	while (getline(file, point_line)){
		vector<string> point_tokens;
		istringstream iss(point_line);
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(point_tokens));

		ENCODED_MOVING_POINT this_emp;
		this_emp.index = stol(point_tokens.at(POINT_ID));
		this_emp.a = stod(point_tokens.at(POINT_X));
		this_emp.b = stod(point_tokens.at(POINT_Y));
		this_emp.radius = stod(point_tokens.at(POINT_RADIUS));

		emp_vector[this_emp.index] = this_emp;
	}

	return emp_vector;
}
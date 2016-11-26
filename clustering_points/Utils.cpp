#include "Utils.h"
#include "MovingPoint.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>

using namespace std;

#pragma warning(disable:4996)
#define TAG 0

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

	f = fopen(filename, "r");

	if (f == NULL){
		printf("cannot open file.\n");
		exit(0);
	}

	// first line is config line - ignore (http://stackoverflow.com/a/16108311/2698072)
	int row = fscanf(f, "%*[^\n]\n", NULL); 

	while (fscanf(f, "%d %lf %lf %lf\n", &index, &x, &y, &r) != EOF) { 
		points.push_back(new MovingPoint(x, y, r));
	}

	fclose(f);

	return points;
}

ENCODED_MOVING_POINT* Utils::getEncodeMovingPointsFromFile(char* filename, int number_of_points){
	double x = 0.0, y = 0.0, r = 0.0;
	int index = 0;
	FILE* f;
	ENCODED_MOVING_POINT* emp_vector = (ENCODED_MOVING_POINT*)malloc(number_of_points * sizeof(ENCODED_MOVING_POINT));

	f = fopen(filename, "r");

	// first line is config line - ignore (http://stackoverflow.com/a/16108311/2698072)
	int row = fscanf(f, "%*[^\n]\n", NULL);

	while (fscanf(f, "%d %lf %lf %lf\n", &index, &x, &y, &r) != EOF) {
		ENCODED_MOVING_POINT this_emp;
		this_emp.index = index;
		this_emp.a = x;
		this_emp.b = y;
		this_emp.radius = r;

		emp_vector[this_emp.index] = this_emp;
	}

	return emp_vector;
}

void Utils::MPI_Custom_send_config(Config cfg, int to){
	long number_of_points = cfg.getTotalPoints();
	long number_of_clusters = cfg.getNumberOfClusters();
	double delta_t = cfg.getDeltaT();
	double time = cfg.getTime();
	long limit = cfg.getLimit();

	MPI_Send(&number_of_points, 1, MPI_LONG, 1, TAG, MPI_COMM_WORLD);
	MPI_Send(&number_of_clusters, 1, MPI_LONG, 1, TAG, MPI_COMM_WORLD);
	MPI_Send(&delta_t, 1, MPI_DOUBLE, 1, TAG, MPI_COMM_WORLD);
	MPI_Send(&time, 1, MPI_DOUBLE, 1, TAG, MPI_COMM_WORLD);
	MPI_Send(&limit, 1, MPI_LONG, 1, TAG, MPI_COMM_WORLD);
}

Config Utils::MPI_Custom_recv_config(int from){
	MPI_Status status;
	long number_of_points = 0;
	long number_of_clusters = 0;
	double delta_t = 0;
	double time = 0;
	long limit = 0;

	MPI_Recv(&number_of_points, 1, MPI_LONG, 0, TAG, MPI_COMM_WORLD, &status);
	MPI_Recv(&number_of_clusters, 1, MPI_LONG, 0, TAG, MPI_COMM_WORLD, &status);
	MPI_Recv(&delta_t, 1, MPI_DOUBLE, 0, TAG, MPI_COMM_WORLD, &status);
	MPI_Recv(&time, 1, MPI_DOUBLE, 0, TAG, MPI_COMM_WORLD, &status);
	MPI_Recv(&limit, 1, MPI_LONG, 0, TAG, MPI_COMM_WORLD, &status);

	return Config(number_of_points, number_of_clusters, delta_t, time, limit);
}
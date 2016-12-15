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
#define MASTER_ID 0

Utils::Utils()
{
}

Utils::~Utils()
{
}

Config Utils::createConfigFromFile(char* filename){
	/**
	Creates a Config object out of input text file

	@param [char* filename] - file name string
	@return [Config] initialized with data from file
	*/

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
	/**
	Creates the moving points vector out of input text file with points

	@param [char* filename] - file name string
	@return [vector<Point*>] - a vector filled with the moving points from the input file.
	*/

	double x = 0.0, y = 0.0, r = 0.0;
	int index = 0;
	vector<Point*> points;
	FILE* f;

	f = fopen(filename, "r");

	if (f == NULL){
		printf("cannot open file.\n");
		exit(0);
	}

	// skip first line is config line (http://stackoverflow.com/a/16108311/2698072)
	int row = fscanf(f, "%*[^\n]\n", NULL); 

	while (fscanf(f, "%d %lf %lf %lf\n", &index, &x, &y, &r) != EOF) { 
		points.push_back(new MovingPoint(x, y, r));
	}

	fclose(f);

	return points;
}

ENCODED_MOVING_POINT* Utils::getEncodeMovingPointsFromFile(char* filename, int number_of_points){
	/**
	Creates an array of ENCODED_MOVING_POINT from the input file

	@param [char* filename] - file name string
	@return [ENCODED_MOVING_POINT*] - an array of ENCODED_MOVING_POINT filled with the moving points from the input file.
	*/

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

void Utils::MPI_Custom_create_moving_point_datatype(MPI_Datatype* MPI_CUSTOM_DATATYPE){
	/**
	Creates a new custom datatype for the encoded moving points

	@param [MPI_Datatype* MPI_CUSTOM_DATATYPE] - reference for the MPI_Datatype object
	@return [void]
	*/

	// based on answer (http://stackoverflow.com/a/20709889/2698072)

	int	number_of_blocks = MOVING_POINT_STRUCT_NUMBER_OF_BLOCKS;
	int	blocks[MOVING_POINT_STRUCT_NUMBER_OF_BLOCKS] = { 1, 1, 1, 1 };

	MPI_Datatype types[MOVING_POINT_STRUCT_NUMBER_OF_BLOCKS] = {    /* pixel internal types */
		MPI_LONG,
		MPI_DOUBLE,
		MPI_DOUBLE,
		MPI_DOUBLE
	};

	MPI_Aint dis[MOVING_POINT_STRUCT_NUMBER_OF_BLOCKS] = {          /* internal displacements */
		offsetof(ENCODED_MOVING_POINT, index),
		offsetof(ENCODED_MOVING_POINT, a),
		offsetof(ENCODED_MOVING_POINT, b),
		offsetof(ENCODED_MOVING_POINT, radius)
	};

	MPI_Type_create_struct(number_of_blocks, blocks, dis, types, MPI_CUSTOM_DATATYPE);
	MPI_Type_commit(MPI_CUSTOM_DATATYPE);
}

void Utils::MPI_Custom_send_config(Config cfg, int to){
	/**
	Using MPI_Send to send the config from master to slave

	@param [Config cfg] - config object to send
	@param [int to] - destenation process id
	@return [void]
	*/

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

void Utils::MPI_Custom_master_broadcast_config(Config* cfg, int myid){
	/**
	Using MPI_Bcast to broadcast the config from master to all slaves

	@param [Config cfg] - config object to send
	@return [void]
	*/

	long number_of_points, number_of_clusters, limit;
	double delta_t, time;

	if (myid == MASTER_ID){
		number_of_points = cfg->getTotalPoints();
		number_of_clusters = cfg->getNumberOfClusters();
		delta_t = cfg->getDeltaT();
		time = cfg->getTime();
		limit = cfg->getLimit();
	}

	MPI_Bcast(&number_of_points, 1, MPI_LONG, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&number_of_clusters, 1, MPI_LONG, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&delta_t, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&time, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&limit, 1, MPI_LONG, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);

	if (myid != MASTER_ID){
		cfg->setTotalPoints(number_of_points);
		cfg->setNumberOfClusters(number_of_clusters);
		cfg->setDeltaT(delta_t);
		cfg->setTime(time);
		cfg->setLimit(limit);
	}
}

Config Utils::MPI_Custom_recv_config(int from){

	/**
	Using MPI_Send to receive the config from master

	@param [int from] - master id
	@return [Config] - Config object created from data received
	*/

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
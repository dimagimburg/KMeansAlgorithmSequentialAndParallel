#pragma once
#include <string>
#include <vector>
#include <mpi.h>
#include "Config.h"
#include "Point.h"
#include "MovingPoint.h"

#define MOVING_POINT_STRUCT_NUMBER_OF_BLOCKS 4
typedef struct encoded_moving_point {
	long index;
	double a;
	double b;
	double radius;
} ENCODED_MOVING_POINT;

class Utils
{
public:
	Utils();
	~Utils();

	static Config createConfigFromFile(char* filename);
	static std::vector<Point*> getMovingPointsFromFile(char* filename);
	static ENCODED_MOVING_POINT* getEncodeMovingPointsFromFile(char* filename, int number_of_points);
	static void MPI_Custom_create_moving_point_datatype(MPI_Datatype *MPI_CUSTOM_DATATYPE);
	static void MPI_Custom_send_config(Config cfg, int to);
	static Config MPI_Custom_recv_config(int from);
};


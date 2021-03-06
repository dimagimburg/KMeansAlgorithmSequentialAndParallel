#pragma once
#include <string>
#include <vector>
#include <mpi.h>
#include "Config.h"
#include "Point.h"
#include "MovingPoint.h"
#include "EncodedMovingPoint.h"

using namespace std;

class Utils
{
public:
	Utils();
	~Utils();

	static Config createConfigFromFile(char* filename);
	static std::vector<Point*> getMovingPointsFromFile(char* filename);
	static void getEncodeMovingPointsFromFile(ENCODED_MOVING_POINT* &emp, char* filename, int number_of_points);
	static void decodeMovingPointsToVector(ENCODED_MOVING_POINT* points_encoded, int numberOfPoints, vector<Point*>& points);
	static void MPI_Custom_create_moving_point_datatype(MPI_Datatype *MPI_CUSTOM_DATATYPE);
	static void MPI_Custom_send_config(Config cfg, int to);
	static void MPI_Custom_master_broadcast_config(Config* cfg, int myid);
	static Config MPI_Custom_recv_config(int from);
	static void printEncodedMovingPoints(string prefix, ENCODED_MOVING_POINT* points, int numberOfPoints);
};


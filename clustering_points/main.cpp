#include <mpi.h>
#include <iostream>
#include "Point.h"
#include "MovingPoint.h"
#include "Cluster.h"
#include "Config.h"
#include "Utils.h"
#include "SequentialKMeans.h"

#define INPUT_FILE_PATH "C:\\tmp\\input.txt"

using namespace std;

// TODO's
// 1. implement point movment in circle based on radius.
// 2. make sure you get all data needed via mpi , and all data is decoded at the end points.
// 3. parallelize the point movment with cuda, all points positions are calculated at once (this is the first parallelizing action).
// 4. make KMEANS alg' parallelized too.

int main(int argc, char *argv[])
{
	// stage 1: initialization
	int myid, numprocs, namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Comm comm;
	MPI_Status status;

	
	//ENCODED_MOVING_POINT* emp_vector = Utils::getEncodeMovingPointsFromFile("input.txt");
	
	//Utils::print_something("WWWSSS");

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Get_processor_name(processor_name, &namelen);
	
	if (myid == 0){
		cout << "I am master" << endl;
		Config cfg = Utils::createConfigFromFile(INPUT_FILE_PATH);
		vector<Point*> points = Utils::getMovingPointsFromFile(INPUT_FILE_PATH);
		
		SequentialKMeans s_kmeans(cfg, &points);
		vector<Cluster> clusters = s_kmeans.getClusters(0);

		cout << "************" << endl;
		cout << clusters.at(0) << endl;
		cout << clusters.at(1) << endl;
		cout << clusters.at(2) << endl;
	}
	else {
		cout << "I am slave" << endl;
	}
	
	// stage 2: send and receive

	/* --------------------------------------------------------------
	vector<Point*> points = Utils::getMovingPointsFromFile("test2.txt");

	SequentialKMeans s_kmeans(config, &points);
	vector<Cluster> clusters = s_kmeans.getClusters(0);

	cout << "************" << endl;
	cout << clusters.at(0) << endl;
	cout << clusters.at(1) << endl;
	cout << clusters.at(2) << endl;
	cout << clusters.at(3) << endl;
	----------------------------------------------------------------- */

	// stage 5? final: close files, free resources, destruct objects
	MPI_Finalize();
	cout << "END" << endl;
	return 0;

}
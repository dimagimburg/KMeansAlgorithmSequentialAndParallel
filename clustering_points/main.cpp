#include <mpi.h>
#include <iostream>
#include "Point.h"
#include "MovingPoint.h"
#include "Cluster.h"
#include "Config.h"
#include "Utils.h"
#include "ParallelKMeans.h"

#define INPUT_FILE_PATH "C:\\tmp\\input.txt"
#define MASTER_ID 0
#define TAG 0

using namespace std;

// TODO's
// 1. implement point movment in circle based on radius.
// 2. make sure you get all data needed via mpi , and all data is decoded at the end points.
// 3. parallelize the point movment with cuda, all points positions are calculated at once (this is the first parallelizing action).
// 4. make KMEANS alg' parallelized too.
// 5. check on big amount of data, can we send 250k points via one mpi call or we need some sort of split.
// 6. error handling for some cases (number of processes is under 2, etc)
// 7. try time T and delta_t not pretty dividable (e.g. 2 processes, delta_t = 0.1, T = 150, each process gets 7500 intervals).
// 8. move constants into a global location so we wont need to duplicate declarations and defines
// 9. check if scattering will help to make the sending of the points more efficient
// 10. change INPUT_FILE_PATH to something more generic
// 11. code conventions, camel case or underscored variables and functions
// 12. code conventions, each variable procces related will start with the prefix my_
// 13. common language, iteration - in the context of delta_t time interval

int main(int argc, char *argv[])
{
	// ======================= stage 1: initialization =======================
	int								myid, numprocs, namelen;
	double							my_start_time, my_end_time;
	char							processor_name[MPI_MAX_PROCESSOR_NAME];
	vector<Point*>					points;
	map<double, vector<Cluster*>>	map_of_time_intervals; // see readme file, Implementation, point 2
	Config							cfg;
	ENCODED_MOVING_POINT*			points_encoded;
	ParallelKMeans*					parallel_kmeans;
	MPI_Comm						comm;
	MPI_Status						status;

	// init of custom datatype for ENCODED_MOVING_POINT struct to send 
	MPI_Datatype					MPI_CUSTOM_ENCODED_MOVING_POINT;

	// MPI init functions
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Get_processor_name(processor_name, &namelen);
	Utils::MPI_Custom_create_moving_point_datatype(&MPI_CUSTOM_ENCODED_MOVING_POINT); // prepare the moving point datatype to send over mpi

	// -------------------------------------------------------------------------
	
	// ======================= stage 2: send and receive =======================
	// 2.1 - initialize config and broadcast it to all processes
	if (myid == MASTER_ID){
		cfg = Utils::createConfigFromFile(INPUT_FILE_PATH);
	}
	Utils::MPI_Custom_master_broadcast_config(&cfg, myid);
	
	// 2.2 - send all data needed to all processes
	
	if (myid == MASTER_ID)
		/*
		had to first encode points into a struct so that myid = 0
		could send it to other processes as serialized data.
		Readme file, Implementation, point 1.
		*/
		Utils::getEncodeMovingPointsFromFile(points_encoded, INPUT_FILE_PATH, cfg.getTotalPoints());
	else
		// slave allocates the memory for coming points
		points_encoded = (ENCODED_MOVING_POINT*)malloc(cfg.getTotalPoints() * sizeof(ENCODED_MOVING_POINT));
	
	MPI_Bcast(points_encoded, cfg.getTotalPoints(), MPI_CUSTOM_ENCODED_MOVING_POINT, MASTER_ID, MPI_COMM_WORLD);

	// 2.3 decode points into vectors
	Utils::decodeMovingPointsToVector(points_encoded, cfg.getTotalPoints(), points);

	// ======================= stage 3: execute algorithm =======================
	// 3.1 - calculate the time intervals range which each proccess is in charge of
	my_start_time	= myid * (cfg.getTime() / numprocs);
	my_end_time		= (myid + 1) * (cfg.getTime() / numprocs);

	// 3.2 - initialize parallel algorithm helper class
	parallel_kmeans = new ParallelKMeans(myid, cfg, &points, my_start_time, my_end_time);

	// 3.3 - get clusters for each time interval in the time range per proccess
	parallel_kmeans->get_clusters_for_all_intervals(map_of_time_intervals);
	// ======================= stage 5? final: close files, free resources, destruct objects =======================
	//free(points_encoded);
	MPI_Type_free(&MPI_CUSTOM_ENCODED_MOVING_POINT);
	MPI_Finalize();
	cout << "END" << endl;
	return 0;

}
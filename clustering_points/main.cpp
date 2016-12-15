#include <mpi.h>
#include <iostream>
#include "Point.h"
#include "MovingPoint.h"
#include "Cluster.h"
#include "Config.h"
#include "Utils.h"
#include "SequentialKMeans.h"

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
// 7. move constants into a global location so we wont need to duplicate declarations and defines

int main(int argc, char *argv[])
{
	// ======================= stage 1: initialization =======================
	int				myid, numprocs, namelen;
	char			processor_name[MPI_MAX_PROCESSOR_NAME];
	Config			cfg;
	MPI_Comm		comm;
	MPI_Status		status;

	// init of custom datatype for ENCODED_MOVING_POINT struct to send 
	MPI_Datatype	MPI_CUSTOM_ENCODED_MOVING_POINT;

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
	if (myid == MASTER_ID){
		/* 
			had to first encode points into a struct so that myid = 0 
			could send it to other processes as serialized data.
			Readme file, Implementation, point 1.
		*/

		ENCODED_MOVING_POINT* points_encoded;
		points_encoded = Utils::getEncodeMovingPointsFromFile(INPUT_FILE_PATH, cfg.getTotalPoints());
		
		// =============================================== test - send 1 point ===============================================
		MPI_Send(&points_encoded, cfg.getTotalPoints(), MPI_CUSTOM_ENCODED_MOVING_POINT, 1, TAG, MPI_COMM_WORLD);
		cout << "MASTER: sent " << cfg.getTotalPoints() << " points" << endl;
		// =============================================== test - send array of points =============================================== 

	
		cout << "[Master end] id=[" << myid << "]" << endl;
	}
	else {
		cout << "[Slave start] id=[" << myid << "]" << endl;
		cout << "[Slave] config.total_points=[" << cfg.getTotalPoints() << "]" << endl;
		MPI_Status status;
		//Config cfg = Utils::MPI_Custom_recv_config(MASTER_ID);

		// =============================================== test - send array of points =============================================== 
		ENCODED_MOVING_POINT* points_encoded_received = (ENCODED_MOVING_POINT*) malloc(cfg.getTotalPoints() * sizeof(ENCODED_MOVING_POINT));
		MPI_Recv(&points_encoded_received, cfg.getTotalPoints(), MPI_CUSTOM_ENCODED_MOVING_POINT, MASTER_ID, TAG, MPI_COMM_WORLD, &status);
		cout << "SLAVE: received " << cfg.getTotalPoints() << " points" << endl;
		// =============================================== test - send array of points =============================================== 


		cout << "[Slave end] id=[" << myid << "]" << endl;
		//free(received);
	}
	
	

	// ======================= stage 5? final: close files, free resources, destruct objects =======================
	MPI_Type_free(&MPI_CUSTOM_ENCODED_MOVING_POINT);
	MPI_Finalize();
	cout << "END" << endl;
	return 0;

}
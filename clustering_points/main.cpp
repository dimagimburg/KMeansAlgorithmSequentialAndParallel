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

int main(int argc, char *argv[])
{
	// ------------------------ stage 1: initialization ------------------------
	int				myid, numprocs, namelen;
	char			processor_name[MPI_MAX_PROCESSOR_NAME];
	MPI_Comm		comm;
	MPI_Status		status;
	// setup of ENCODED_MOVING_POINT struct to send 
	MPI_Datatype	MPI_CUSTOM_ENCODED_MOVING_POINT, oldtypes[2];
	MPI_Aint		offsets[2], extent;
	int				blockcounts[2];

	// MPI init functions
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Get_processor_name(processor_name, &namelen);

	/* ENCODED_MOVING_POINT struct
		typedef struct encoded_moving_point {
			long index;
			double a;
			double b;
			double radius;
		} ENCODED_MOVING_POINT;
	*/
	// setup description of ENCODED_MOVING_POINT struct
	// first setup of 1 MPI_LONG - index
	offsets[0]		=	0;
	oldtypes[0]		=	MPI_LONG;
	blockcounts[0]	=	1;

	// setup description of the 3 MPI_DOUBLE a, b, radius
	// need to first figure offset by getting size of MPI_FLOAT
	MPI_Type_extent(MPI_LONG, &extent);

	offsets[1]		=	1 * extent;
	oldtypes[1]		=	MPI_DOUBLE;
	blockcounts[1]	=	3;

	// define structured type and commit it
	MPI_Type_struct(2, blockcounts, offsets, oldtypes, &MPI_CUSTOM_ENCODED_MOVING_POINT);
	MPI_Type_commit(&MPI_CUSTOM_ENCODED_MOVING_POINT);

	// -------------------------------------------------------------------------
	
	if (myid == MASTER_ID){
		cout << "[Master start] id=[" << myid << "]" << endl;
		Config cfg = Utils::createConfigFromFile(INPUT_FILE_PATH);

		/* 
			had to first encode points into a struct so that myid = 0 
			could send it to other processes as serialized data 
		*/

		ENCODED_MOVING_POINT* points_encoded;
		points_encoded = Utils::getEncodeMovingPointsFromFile(INPUT_FILE_PATH, cfg.getTotalPoints());
		Utils::MPI_Custom_send_config(cfg, 1);
		//MPI_Send(&points_encoded, cfg.getTotalPoints(), MPI_CUSTOM_ENCODED_MOVING_POINT, 1, TAG, MPI_COMM_WORLD);
		cout << "[Master end] id=[" << myid << "]" << endl;
	}
	else {
		cout << "[Slave start] id=[" << myid << "]" << endl;
		MPI_Status status;
		ENCODED_MOVING_POINT* received;

		Config cfg = Utils::MPI_Custom_recv_config(MASTER_ID);

		cout << cfg.getTotalPoints() << endl;
		cout << cfg.getNumberOfClusters() << endl;
		cout << cfg.getDeltaT() << endl;
		cout << cfg.getTime() << endl;
		cout << cfg.getLimit() << endl;

		cout << "[Slave end] id=[" << myid << "]" << endl;
	}
	
	// stage 2: send and receive

	// stage 5? final: close files, free resources, destruct objects
	MPI_Finalize();
	cout << "END" << endl;
	return 0;

}
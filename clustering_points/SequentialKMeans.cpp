#include "SequentialKMeans.h"
#include <iostream>

using namespace std;

SequentialKMeans::SequentialKMeans(Config config, vector<MovingPoint>* points) : config(config), points(points)
{
}


SequentialKMeans::~SequentialKMeans()
{
}

vector<Cluster> SequentialKMeans::getClusters(double current_time){
	vector<Cluster> clusters;
	initialize_clusters_vector(clusters);
	return clusters;
}

void SequentialKMeans::initialize_clusters_vector(vector<Cluster>& clusters){
	for (int i = 0; i < config.getNumberOfClusters(); i++){
		cout << "initalize cluster number " << i + 1 << endl;
	}
}

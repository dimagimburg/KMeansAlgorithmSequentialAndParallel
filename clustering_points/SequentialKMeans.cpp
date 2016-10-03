#include "SequentialKMeans.h"
#include <iostream>

using namespace std;

SequentialKMeans::SequentialKMeans(Config config, vector<Point*>* points) : config(config), points(points)
{
	cout << config << endl;
}


SequentialKMeans::~SequentialKMeans()
{
}

vector<Cluster*> SequentialKMeans::getClusters(double current_time){
	vector<Cluster*> clusters;
	initialize_clusters_vector(clusters);

	for (int i = config.getNumberOfClusters(); i < config.getTotalPoints(); i++){

		Cluster* min_distance_cluster = clusters.at(0);
		double min_distance = (*points).at(i)->getDistanceFrom(*(min_distance_cluster->getCenter()));
		for (int j = 0; j < config.getNumberOfClusters(); j++){			
			double new_distance = (*points).at(i)->getDistanceFrom(*(clusters.at(j)->getCenter()));
			if (new_distance < min_distance){
				min_distance_cluster = clusters.at(j);
				min_distance = new_distance;
			}
		}
		min_distance_cluster->addPoint((*points).at(i));
	}

	return clusters;
}

void SequentialKMeans::initialize_clusters_vector(vector<Cluster*>& clusters){
	for (int i = 0; i < config.getNumberOfClusters(); i++){
		clusters.push_back(new Cluster((*points).at(i)));
	}
}

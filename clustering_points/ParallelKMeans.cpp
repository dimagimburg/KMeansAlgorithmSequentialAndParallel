#include "ParallelKMeans.h"
#include <omp.h>
#include <iostream>

using namespace std;

ParallelKMeans::ParallelKMeans(int my_id, Config config, vector<Point*>* points, double my_start_time, double my_end_time) :
my_id(my_id),
config(config),
points(points),
my_start_time(my_start_time),
my_end_time(my_end_time)
{
	cout << config << endl;
}

ParallelKMeans::~ParallelKMeans()
{
}

vector<Cluster> ParallelKMeans::getClusters(double current_time){
	vector<Cluster> current_clusters;
	vector<Cluster> previous_clusters;
	initialize_clusters_vector(current_clusters);
	initialize_clusters_vector(previous_clusters);

	k_means_iteration(current_clusters);
	k_means_iteration(previous_clusters);

	for (int i = 1; i < config.getLimit(); i++){

		k_means_iteration(current_clusters);

		if (current_clusters == previous_clusters){
			// algorithm ends
			cout << "algorithm ends before limit, clusters are equal, KMeans iterations over after " << i << " iterations" << endl;
			return current_clusters;
		}

		copy_cluster_vector(current_clusters, previous_clusters);
	}



	return current_clusters;
}

void ParallelKMeans::initialize_clusters_vector(vector<Cluster>& clusters){
	for (int i = 0; i < config.getNumberOfClusters(); i++){
		clusters.push_back(Cluster((*points).at(i)));
	}
}

void ParallelKMeans::k_means_iteration(vector<Cluster>& clusters){
	vector<Cluster>::iterator itr = clusters.begin();
	vector<Cluster>::iterator itrEnd = clusters.end();

	for (; itr != itrEnd; ++itr)
	{
		vector<Point*> cluster_pts = (*(*itr).getPoints());
		if (cluster_pts.size() > 0){
			clear_points_vector_for_cluster((*itr));
		}
	}

	for (int i = 0; i < config.getTotalPoints(); i++){

		// assumption the min distance is the first cluster
		Cluster* min_distance_cluster = &clusters.at(0);
		double min_distance = (*points).at(i)->getDistanceFrom(*((*min_distance_cluster).getCenter()));

		// TODO: convert this loop to iterator (if possible)

		for (int j = 1; j < config.getNumberOfClusters(); j++){
			double new_distance = (*points).at(i)->getDistanceFrom(*(clusters.at(j).getCenter()));
			if (new_distance < min_distance){
				min_distance_cluster = &clusters.at(j);
				min_distance = new_distance;
			}
		}
		(*min_distance_cluster).addPoint((*points).at(i));
	}

	itr = clusters.begin();
	for (; itr != itrEnd; ++itr)
	{
		(*itr).recenter();
	}
}

void ParallelKMeans::copy_cluster_vector(vector<Cluster>& from, vector<Cluster>& to){
	// clear to vector
	to.clear();

	// hard copy from "from" vector to "to" vector
	vector<Cluster>::iterator itr = from.begin();
	vector<Cluster>::iterator itrEnd = from.end();
	for (; itr != itrEnd; ++itr)
	{
		Cluster c((*itr).getCenter());
		vector<Point*>::const_iterator point_itr = (*((*itr).getPoints())).begin();
		vector<Point*>::const_iterator point_itrEnd = (*((*itr).getPoints())).end();
		for (; point_itr != point_itrEnd; ++point_itr){
			c.addPoint(*point_itr);
		}
		to.push_back(c);
	}
}

void ParallelKMeans::clear_points_vector_for_cluster(Cluster& to_clear){
	if (to_clear.size() > 0){
		/* // commented it out because the delete of the pointers actually also delete them from this->points
		vector<Point*>::const_iterator point_itr = (*(to_clear.getPoints())).begin();
		vector<Point*>::const_iterator point_itrEnd = (*(to_clear.getPoints())).end();
		for (; point_itr != point_itrEnd; ++point_itr)
		{
		delete *point_itr;
		}
		*/
		to_clear.clear();
	}
}

void ParallelKMeans::get_clusters_for_all_intervals(map<double, vector<Cluster*>>& iterations){
	int number_of_iterations = ((int) (my_end_time - my_start_time)) / config.getDeltaT();
	cout << my_id << ", iterations: " << number_of_iterations << endl;
	#pragma omp parallel shared(iterations)
	{
		int numberOfThreads = omp_get_num_threads(); // default choise made by omp
		const int myThreadId = omp_get_thread_num();

		#pragma omp for
		for (int i = 0; i < number_of_iterations; i++){
			
		}
	}
}
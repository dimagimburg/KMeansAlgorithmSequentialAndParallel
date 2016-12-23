#pragma once
#include "Config.h"
#include "Point.h"
#include "MovingPoint.h"
#include "Cluster.h"
#include <vector>
#include <map>


class ParallelKMeans
{
private:
	void initialize_clusters_vector(vector<Cluster>& clusters);
	void k_means_iteration(vector<Cluster>& clusters);
	void copy_cluster_vector(vector<Cluster>& from, vector<Cluster>& to);
	void clear_clusters_vector(vector<Cluster>& to_clear);
	void clear_points_vector_for_cluster(Cluster& to_clear);

public:
	Config config;
	std::vector<Point*>* points;
	int my_id;
	double my_start_time;
	double my_end_time;

	ParallelKMeans(int my_id, Config config, vector<Point*>* points, double start_point_index, double end_point_index);
	~ParallelKMeans();

	std::vector<Cluster> getClusters(double current_time);
	void get_clusters_for_all_intervals(map<double, vector<Cluster*>>& iterations);
};
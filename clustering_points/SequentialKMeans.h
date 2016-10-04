#pragma once
#include "Config.h"
#include "Point.h"
#include "MovingPoint.h"
#include "Cluster.h"
#include <vector>

class SequentialKMeans
{
private:
	void initialize_clusters_vector(vector<Cluster*>& clusters);
	void k_means_iteration(vector<Cluster*>& clusters);
	bool cluster_vectors_equal(vector<Cluster*>& previous, vector<Cluster*>& current);
	void clear_clusters_vector(vector<Cluster*>& to_clear);
	void copy_cluster_vector(vector<Cluster*>& from, vector<Cluster*>& to);
	void clear_points_vector(vector<Point*>& to_clear);

public:
	Config config;
	std::vector<Point*>* points;

	SequentialKMeans(Config config, vector<Point*>* points);
	~SequentialKMeans();

	std::vector<Cluster*> getClusters(double current_time);
};


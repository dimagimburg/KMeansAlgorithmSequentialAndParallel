#pragma once
#include "Config.h"
#include "Point.h"
#include "MovingPoint.h"
#include "Cluster.h"
#include <vector>

class SequentialKMeans
{
public:
	Config config;
	std::vector<MovingPoint>* points;

	SequentialKMeans(Config config, std::vector<MovingPoint>* points);
	~SequentialKMeans();

	std::vector<Cluster> getClusters(double current_time);

	void initialize_clusters_vector(vector<Cluster>& clusters);
};


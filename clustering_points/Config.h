#pragma once
#include <iostream>

class Config
{
private:
	int total_points;
	int n_clusters;
	double delta_t;
	double time;
	int limit;

public:
	Config();
	Config(int total_points, int n_clusters, double delta_t, double time, int limit);
	~Config();

	int getTotalPoints();
	int getNumberOfClusters();
	double getDeltaT();
	double getTime();
	int getLimit();

	void setTotalPoints(int total_points);
	void setNumberOfClusters(int n_clusters);
	void setDeltaT(double delta_t);
	void setTime(double time);
	void setLimit(int limit);

	friend std::ostream& operator<<(std::ostream& os, const Config& c)
	{
		os << "=========================" << std::endl;
		os << "Config:" << std::endl;
		os << "-------------------------" << std::endl;
		os << "Total Points: " << c.total_points << std::endl;
		os << "Number of Clusters: " << c.n_clusters << std::endl;
		os << "Delta T: " << c.delta_t << std::endl;
		os << "Time: " << c.time << std::endl;
		os << "Limit: " << c.limit << std::endl;
		os << "=========================" << std::endl;
		return os;
	}
};


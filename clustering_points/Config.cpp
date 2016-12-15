#include "Config.h"

Config::Config(int total_points, int n_clusters, double delta_t, double time, int limit) : 
	total_points(total_points),
	n_clusters(n_clusters), 
	delta_t(delta_t), 
	time(time),
	limit(limit)
{}

Config::Config(){
	this->setTotalPoints(0);
	this->setNumberOfClusters(0);
	this->setDeltaT(0);
	this->setTime(0);
	this->setLimit(0);
}

Config::~Config(){};

int Config::getTotalPoints(){
	return total_points;
};

int Config::getNumberOfClusters(){
	return n_clusters;
};

double Config::getDeltaT(){
	return delta_t;
};

double Config::getTime(){
	return time;
};

int Config::getLimit(){
	return limit;
};

void Config::setTotalPoints(int total_points){
	this->total_points = total_points;
};

void Config::setNumberOfClusters(int n_clusters){
	this->n_clusters = n_clusters;
};

void Config::setDeltaT(double delta_t){
	this->delta_t = delta_t;
};

void Config::setTime(double time){
	this->time = time;
};

void Config::setLimit(int limit){
	this->limit = limit;
};
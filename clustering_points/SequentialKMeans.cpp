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
	vector<Cluster*> previous_clusters_vector;
	vector<Cluster*> current_clusters;
	bool clusters_equals = false;

	initialize_clusters_vector(previous_clusters_vector);
	initialize_clusters_vector(current_clusters);
	k_means_iteration(current_clusters);
	k_means_iteration(previous_clusters_vector);



	//cout << previous_clusters_vector.size() << endl;
	//previous_clusters_vector = current_clusters;
	//cout << previous_clusters_vector.size() << endl;
	
	
	for (int i = 1; i < 10/*config.getLimit()*/; i++){
		k_means_iteration(previous_clusters_vector);
		/*
		//clear_clusters_vector(current_clusters);
		k_means_iteration(current_clusters);

		if (cluster_vectors_equal(previous_clusters_vector, current_clusters)){
			// algorithm ends
			return current_clusters;
		}
		previous_clusters_vector = current_clusters;
		*/
	}

	


	//cout << previous_clusters_vector.size() << endl;
	//cout << current_clusters.size() << endl;
	//k_means_iteration(current_clusters);
	
	

	return current_clusters;
}

void SequentialKMeans::initialize_clusters_vector(vector<Cluster*>& clusters){
	for (int i = 0; i < config.getNumberOfClusters(); i++){
		clusters.push_back(new Cluster((*points).at(i)));
	}
}

void SequentialKMeans::k_means_iteration(vector<Cluster*>& clusters){
	// clear points
	vector<Cluster*>::const_iterator itr = clusters.begin();
	vector<Cluster*>::const_iterator itrEnd = clusters.end();
	for (; itr != itrEnd; ++itr)
	{
		vector<Point*> cluster_pts = (*(*(*itr)).getPoints());
		if (cluster_pts.size() > 0){
			clear_points_vector(cluster_pts);
		}
	}

	for (int i = 0; i < config.getTotalPoints(); i++){

		// assumption the min distance is the first cluster
		Cluster* min_distance_cluster = clusters.at(0); 
		double min_distance = (*points).at(i)->getDistanceFrom(*(min_distance_cluster->getCenter()));

		// TODO: convert this loop to iterator (if possible)
		for (int j = 0; j < config.getNumberOfClusters(); j++){
			double new_distance = (*points).at(i)->getDistanceFrom(*(clusters.at(j)->getCenter()));
			if (new_distance < min_distance){
				min_distance_cluster = clusters.at(j);
				min_distance = new_distance;
			}
		}
		min_distance_cluster->addPoint((*points).at(i));
	}

	itr = clusters.begin();
	for (; itr != itrEnd; ++itr)
	{
		(*(*itr)).recenter();
	}
}

bool SequentialKMeans::cluster_vectors_equal(vector<Cluster*>& previous, vector<Cluster*>& current){
	// Equals operator on STL vector of pointers http://stackoverflow.com/questions/39855341/equals-operator-on-stl-vector-of-pointers
	return
		(previous.size() == current.size()) &&
		equal(
			begin(previous), end(previous),
			begin(current),
			[](const Cluster* lhs, const Cluster* rhs){ return *lhs == *rhs; }
		);
}

void SequentialKMeans::copy_cluster_vector(vector<Cluster*>& from, vector<Cluster*>& to){
	// clear to vector
	clear_clusters_vector(to);

	// hard copy from "from" vector to "to" vector
	vector<Cluster*>::const_iterator itr = from.begin();
	vector<Cluster*>::const_iterator itrEnd = from.end();
	for (; itr != itrEnd; ++itr)
	{
		// Point* new_center = new Point((*(*(*itr)).getCenter()).getX(), (*(*(*itr)).getCenter()).getY());
		// Cluster* c = new Cluster(new_center);
		Cluster* c = new Cluster((*(*itr)).getCenter());
		to.push_back(c);
		vector<Point*>::const_iterator point_itr = (*((*(*itr)).getPoints())).begin();
		vector<Point*>::const_iterator point_itrEnd = (*((*(*itr)).getPoints())).end();
		for (; point_itr != point_itrEnd; ++point_itr){
			(*c).addPoint(*point_itr);
		}
	}
}

void SequentialKMeans::clear_clusters_vector(vector<Cluster*>& to_clear){
	for (vector< Cluster* >::iterator it = to_clear.begin(); it != to_clear.end(); ++it)
	{
		delete (*it);
	}
	to_clear.clear();
}

void SequentialKMeans::clear_points_vector(vector<Point*>& to_clear){
	for (vector< Point* >::iterator it = to_clear.begin(); it != to_clear.end(); ++it)
	{
		delete *it;
	}
	// TODO IMPLEMENT VIRTUAL DESTRUCTOR!
	to_clear.clear();
}

#pragma once
#include <string>
#include <vector>
#include "Config.h"
#include "Point.h"
#include "MovingPoint.h"

typedef struct encoded_moving_point {
	long index;
	double a;
	double b;
	double radius;
} ENCODED_MOVING_POINT;

class Utils
{
public:
	Utils();
	~Utils();

	static Config createConfigFromFile(std::string filename);
	static std::vector<Point*> getMovingPointsFromFile(std::string filename);
	static ENCODED_MOVING_POINT* getEncodeMovingPointsFromFile(std::string filename);
};


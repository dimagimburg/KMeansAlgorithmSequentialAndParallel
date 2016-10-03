#pragma once
#include <string>
#include <vector>
#include "Config.h"
#include "Point.h"
#include "MovingPoint.h"

class Utils
{
public:
	Utils();
	~Utils();

	static Config createConfigFromFile(std::string filename);
	static std::vector<MovingPoint> getMovingPointsFromFile(std::string filename);
};


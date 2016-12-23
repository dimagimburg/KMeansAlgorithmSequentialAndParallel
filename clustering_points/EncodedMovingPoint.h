#pragma once

#define MOVING_POINT_STRUCT_NUMBER_OF_BLOCKS 4

typedef struct encoded_moving_point {
	int index;
	double a;
	double b;
	double radius;
} ENCODED_MOVING_POINT;
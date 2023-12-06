#pragma once

#include <vector>

class Curve
{
public:

	Curve(float r1x, float r1y, float r2x, float r2y, float p1x, float p1y, float p2x, float p2y)
		: R1x(r1x), R1y(r1y), R2x(r2x), R2y(r2y), P1x(p1x), P1y(p1y), P2x(p2x), P2y(p2y)
	{}

	float R1x;
	float R1y;
	float R2x;
	float R2y;
	float P1x;
	float P1y;
	float P2x;
	float P2y;

	std::pair<float, float> FindPoint(float t)
	{
		/*
		
		P1 = R1
		P2 = P1
		P3 = P2
		P4 = R2
		
		*/

		std::pair<float, float> Point;
		Point.second = (R1y * (1 - (3 * t) + (3 * t * t) - (t * t * t))) + (P1y * ((3 * t) - (6 * t * t) + (3 * t * t * t)) + (P2y * ((3 * t * t) - (3 * t * t * t))) + (R2y * t * t * t));
		Point.first = (R1x * (1 - (3 * t) + (3 * t * t) - (t * t * t))) + (P1x * ((3 * t) - (6 * t * t) + (3 * t * t * t)) + (P2x * ((3 * t * t) - (3 * t * t * t))) + (R2x * t * t * t));
		return Point;
	}

};
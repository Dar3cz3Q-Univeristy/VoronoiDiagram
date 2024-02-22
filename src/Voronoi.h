#pragma once
#include "Point.h"
#include "Edge.h"
#include "Delunay.h"

class Voronoi
{
public:
	Point optimalPlace;
	std::vector<Triangle> sites;
	std::vector<Point> verticies;
	std::vector<Edge> edges;
	Voronoi() = default;
	Voronoi(const Delunay&);
};


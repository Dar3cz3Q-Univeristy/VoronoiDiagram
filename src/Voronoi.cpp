#include "pch.h"
#include "Voronoi.h"

Voronoi::Voronoi(const Delunay& triangulation)
{
	std::vector<Point> verticies;
	std::vector<Edge> edges;
	std::vector<Triangle> sites;

	double distance = -FLT_MAX;
	Point optimal{};
	Point begin(0, 0), end(1, 1);

	for (auto& mainTriangle : triangulation.borders) {
		Triangle tempTriangle = mainTriangle;
		sites.push_back(tempTriangle);

		Point tempPoint = mainTriangle.circumCenter;
		verticies.push_back(tempPoint);

		for (auto& triangle : triangulation.borders) {
			if (mainTriangle.sharesEdge(triangle)) {
				Point p1 = mainTriangle.circumCenter;
				Point p2 = triangle.circumCenter;
				Edge tempEdge(p1, p2);
				edges.push_back(tempEdge);
			}
		}

		for (auto& vertex : mainTriangle.verticies) {
			Point p1 = mainTriangle.circumCenter;
			Point p2 = vertex;
			double d = p1.calculateSquareDistance(p2);
			if (d > distance) {
				if (p1 > begin && p1 < end) {
					distance = d;
					optimal = p1;
				}
			}
		}
	}

	this->optimalPlace = optimal;
	this->verticies = verticies;
	this->edges = edges;
}

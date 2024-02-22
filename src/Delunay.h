#pragma once
#include "Triangle.h"
#include "Edge.h"

class Delunay
{
public:
	double maxX;
	double maxY;
	std::vector<Triangle> borders;
	Delunay(std::vector<Point>&);
	Triangle generateSuperTriangle();
	std::unordered_set<Triangle, Triangle::HashFunction> findBadTriangles(Point&, std::vector<Triangle>&);
	std::vector<Edge> addAllEdges(std::unordered_set<Triangle, Triangle::HashFunction>&);
	std::unordered_set<Edge, Edge::HashFunction> findHoleBoundaries(std::vector<Edge>&);
	void removeBadTriangles(std::vector<Triangle>&, std::unordered_set<Triangle, Triangle::HashFunction>&);
	void createNewTriangles(Point&, std::vector<Triangle>&, std::unordered_set<Edge, Edge::HashFunction>&);
	void cleanUpTriangulation(std::vector<Triangle>&, Triangle&);
	friend std::ostream& operator<<(std::ostream& os, const Delunay& d);
};


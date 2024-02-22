#include "pch.h"
#include "Delunay.h"

Delunay::Delunay(std::vector<Point>& pointList)
{
	//BowyerWatson

	std::vector<Triangle> triangulation;

	this->maxX = 1;
	this->maxY = 1;

	Triangle superTriangle = generateSuperTriangle();
	triangulation.push_back(superTriangle);

	for (auto& point : pointList) {
		std::unordered_set<Triangle, Triangle::HashFunction> badTriangles = findBadTriangles(point, triangulation);

		std::vector<Edge> allEdges = addAllEdges(badTriangles);

		std::unordered_set<Edge, Edge::HashFunction> polygon = findHoleBoundaries(allEdges);

		removeBadTriangles(triangulation, badTriangles);

		createNewTriangles(point, triangulation, polygon);
	}

	cleanUpTriangulation(triangulation, superTriangle);

	this->borders = triangulation;
}

std::unordered_set<Triangle, Triangle::HashFunction> Delunay::findBadTriangles(Point& p, std::vector<Triangle>& t)
{
	std::unordered_set<Triangle, Triangle::HashFunction> result;

	for (auto& triangle : t) {
		if (triangle.isPointInsideCircumcircle(p)) {
			result.insert(triangle);
		}
	}

	return result;
}

std::vector<Edge> Delunay::addAllEdges(std::unordered_set<Triangle, Triangle::HashFunction>& bt)
{
	std::vector<Edge> result;

	for (auto& triangle : bt) {
		Point p1 = triangle.verticies[0];
		Point p2 = triangle.verticies[1];
		Point p3 = triangle.verticies[2];

		Edge e1(p1, p2);
		Edge e2(p2, p3);
		Edge e3(p1, p3);

		result.push_back(e1);
		result.push_back(e2);
		result.push_back(e3);
	}

	return result;
}

std::unordered_set<Edge, Edge::HashFunction> Delunay::findHoleBoundaries(std::vector<Edge>& ae)
{
	std::unordered_set<Edge, Edge::HashFunction> edges;

	for (auto& edge : ae) {
		int count = std::count_if(ae.begin(), ae.end(), [edge](Edge& e) { return e == edge; });
		if (count == 1) {
			edges.insert(edge);
		}
	}

	return edges;
}

void Delunay::removeBadTriangles(std::vector<Triangle>& t, std::unordered_set<Triangle, Triangle::HashFunction>& bt)
{
	for (auto& triangle : bt) {
		std::erase_if(t, [triangle](Triangle& t) {return t == triangle; });
	}
}

void Delunay::cleanUpTriangulation(std::vector<Triangle>& t, Triangle& st)
{
	std::vector<Triangle> toBeRemoved;

	for (auto& triangle : t) {
		if (triangle.sharesVertex(st)) {
			toBeRemoved.push_back(triangle);
		};
	}

	for (auto& triangle : toBeRemoved) {
		std::erase_if(t, [triangle](Triangle t) {return t == triangle; });
	}
}

Triangle Delunay::generateSuperTriangle()
{
	double margin = 1;
	Point p1(-101, 0.5 * this->maxX, -2 * this->maxX - margin);
	Point p2(-102, -2 * this->maxY - margin, 2 * this->maxY + margin);
	Point p3(-103, 2 * this->maxX + maxY + margin, 2 * this->maxY + margin);

	return Triangle(p1, p2, p3);
}

void Delunay::createNewTriangles(Point& n, std::vector<Triangle>& t, std::unordered_set<Edge, Edge::HashFunction>& p)
{
	for (auto& edge : p) {
		Point p1 = edge.p1;
		Point p2 = edge.p2;
		Triangle temp(p1, p2, n);
		t.push_back(temp);
	}
}

std::ostream& operator<<(std::ostream& os, const Delunay& d)
{
	for (auto& border : d.borders) {
		os << border;
	}
	return os;
}

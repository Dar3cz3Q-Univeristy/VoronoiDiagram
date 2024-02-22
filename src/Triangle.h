#pragma once
#include "Point.h"
#include "Edge.h"

class Triangle
{
public:
	Point verticies[3];
	Point circumCenter;
	double radiusSquared;
	Triangle() = default;
	Triangle(Point&, Point&, Point&);
	void updateCircumCenter();
	bool isCounterClockwise(Point&, Point&, Point&);
	bool isPointInsideCircumcircle(Point&) const;
	bool sharesVertex(Triangle&) const;
	bool sharesEdge(const Triangle&) const;
	friend bool operator==(const Triangle&, const Triangle&);
	friend std::ostream& operator<<(std::ostream& os, const Triangle& t);

	struct HashFunction
	{
		size_t operator()(const Triangle& t) const
		{
			size_t p1Hash = std::hash<Point>()(t.verticies[0]);
			size_t p2Hash = std::hash<Point>()(t.verticies[1]);
			size_t p3Hash = std::hash<Point>()(t.verticies[2]);
			return p1Hash ^ p2Hash ^ p3Hash;
		}
	};
};


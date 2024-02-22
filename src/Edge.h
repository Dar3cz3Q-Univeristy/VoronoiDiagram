#pragma once
#include "Point.h"

class Edge
{
public:
	Point p1;
	Point p2;
	Edge() = default;
	Edge(Point&, Point&);
	bool operator==(const Edge&) const;
	friend std::ostream& operator<<(std::ostream& os, const Edge& e);

	struct HashFunction
	{
		size_t operator()(const Edge& e) const
		{
			size_t p1Hash = std::hash<Point>()(e.p1);
			size_t p2Hash = std::hash<Point>()(e.p2);
			return p1Hash ^ p2Hash;
		}
	};
};


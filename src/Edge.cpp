#include "pch.h"
#include "Edge.h"

Edge::Edge(Point& p1, Point& p2)
{
	this->p1 = p1;
	this->p2 = p2;
}

bool Edge::operator==(const Edge& e) const
{
	bool samePoints = this->p1 == e.p1 && this->p2 == e.p2;
	bool samePointsReversed = this->p1 == e.p2 && this->p2 == e.p1;
	return samePoints || samePointsReversed;
}

std::ostream& operator<<(std::ostream& os, const Edge& e)
{
	os << e.p1 << " -> " << e.p2;
	return os;
}

#include "pch.h"
#include "Triangle.h"

Triangle::Triangle(Point& p1, Point& p2, Point& p3) : radiusSquared(0)
{
	if (p1 == p2 || p1 == p3 || p2 == p3) {
		std::cout << "The points must be different\n";
		return;
	}

	if (!isCounterClockwise(p1, p2, p3)) {
		this->verticies[0] = p1;
		this->verticies[1] = p3;
		this->verticies[2] = p2;
	}
	else {
		this->verticies[0] = p1;
		this->verticies[1] = p2;
		this->verticies[2] = p3;
	}

	updateCircumCenter();
}

void Triangle::updateCircumCenter()
{
	Point p0 = verticies[0];
	Point p1 = verticies[1];
	Point p2 = verticies[2];

	double dA = pow(p0.x, 2) + pow(p0.y, 2);
	double dB = pow(p1.x, 2) + pow(p1.y, 2);
	double dC = pow(p2.x, 2) + pow(p2.y, 2);

	double aux1 = (dA * (p2.y - p1.y) + dB * (p0.y - p2.y) + dC * (p1.y - p0.y));
	double aux2 = -(dA * (p2.x - p1.x) + dB * (p0.x - p2.x) + dC * (p1.x - p0.x));
	double div = (2 * (p0.x * (p2.y - p1.y) + p1.x * (p0.y - p2.y) + p2.x * (p1.y - p0.y)));

	if (div == 0) {
		return;
	}

	Point center(aux1 / div, aux2 / div);

	this->circumCenter = center;

	this->radiusSquared = (center.x - p0.x) * (center.x - p0.x) + (center.y - p0.y) * (center.y - p0.y);
}

bool Triangle::isCounterClockwise(Point& p1, Point& p2, Point& p3)
{
	double result = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
	return result > 0;
}

bool Triangle::isPointInsideCircumcircle(Point& p) const
{
	double distance = this->circumCenter.calculateSquareDistance(p);
	return distance < this->radiusSquared;
}

bool Triangle::sharesVertex(Triangle& t) const
{
	for (auto& ownVertex : this->verticies) {
		for (auto& guestVertex : t.verticies) {
			if (ownVertex == guestVertex) {
				return true;
			}
		}
	}
	return false;
}

bool Triangle::sharesEdge(const Triangle& t) const
{
	int counter = 0;

	for (auto& ownVertex : this->verticies) {
		for (auto& guestVertex : t.verticies) {
			if (ownVertex == guestVertex) {
				counter++;
			}
		}
	}

	return counter == 2;
}

bool operator==(const Triangle& t1, const Triangle& t2)
{
	if (t1.circumCenter != t2.circumCenter) {
		return false;
	}

	if (t1.radiusSquared != t2.radiusSquared) {
		return false;
	}

	for (int i = 0; i < 3; i++) {
		if (t1.verticies[i] != t2.verticies[i]) {
			return false;
		}
	}

	return true;
}

std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
	os << "Circumcenter: " << t.circumCenter << "\nRadius squared: " << t.radiusSquared << "\n";
	os << "Verticies:\n";
	for (auto& vertex : t.verticies) {
		os << vertex << "\n";
	}
	return os;
}

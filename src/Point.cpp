#include "pch.h"
#include "Point.h"

Point::Point(double x, double y)
{
	this->id = -1;
	this->x = x;
	this->y = y;
	this->precision = 5;
}

Point::Point(int id, double x, double y)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->precision = 5;
}

void Point::setPrecision(int x)
{
	this->precision = x;
}

double Point::calculateSquareDistance(Point& p) const
{
	return (pow(this->x - p.x, 2) + pow(this->y - p.y, 2));
}

bool operator<(const Point& p1, const Point& p2)
{
	return p1.x < p2.x && p1.y < p2.y;
}

bool operator>(const Point& p1, const Point& p2)
{
	return !(p1 < p2);
}

bool operator==(const Point& pl, const Point& pr)
{
	return pl.x == pr.x && pl.y == pr.y;
}

bool operator!=(const Point& pl, const Point& pr)
{
	return !(pl == pr);
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << "Point ID: " << p.id << std::setprecision(p.precision) << ", x: " << p.x << ", y: " << p.y;
	return os;
}

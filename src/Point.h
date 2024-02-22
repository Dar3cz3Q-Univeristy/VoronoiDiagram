#pragma once

class Triangle;

class Point
{
public:
	int id;
	double x;
	double y;
	int precision;
	Point() = default;
	Point(double, double);
	Point(int, double, double);
	void setPrecision(int);
	double calculateSquareDistance(Point&) const;
	friend bool operator<(const Point&, const Point&);
	friend bool operator>(const Point&, const Point&);
	friend bool operator==(const Point&, const Point&);
	friend bool operator!=(const Point&, const Point&);
	friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

template <>
struct std::hash<Point> {
	size_t operator()(const Point& p) const noexcept {
		size_t xHash = std::hash<double>()(p.x);
		size_t yHash = std::hash<double>()(p.y);
		return xHash ^ yHash;
	}
};
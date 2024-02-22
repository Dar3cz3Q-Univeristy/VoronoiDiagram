#include "Header.h"

int main()
{
	std::string fileName{};
	int precision{};

	std::cout << "Provide file name (csv extension): ";

	std::cin >> fileName;

	std::cout << "Set precision (decimal places): ";

	std::cin >> precision;

	std::vector<Point> points = initializePoints(fileName);

	if (points.empty()) {
		return -1;
	}

	Delunay triangulacja(points);

	Voronoi diagram = triangulacja;

	Point optimalPlace = diagram.optimalPlace;

	if (precision != 0) {
		optimalPlace.setPrecision(precision);
	}

	std::cout << "Optimal place:\n" << optimalPlace << "\n";

	visualizeData(triangulacja, diagram, optimalPlace, points);

	std::cout << "Data to visualize is in file visualize.txt";

	return 0;
}


#include "Header.h"

std::vector<Point> initializePoints(std::string fileName) {
	std::ifstream file;
	file.open(fileName);

	if (!file.good()) {
		std::cerr << "Cannot open file\n";
		return std::vector<Point>();
	}

	std::string line, colname;
	double val;

	std::vector<Point> result;

	std::getline(file, line);

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		int colIndex = 0;
		double values[3] = { 0 };

		while (ss >> val) {
			if (ss.peek() == ',') {
				ss.ignore();
			}
			values[colIndex] = val;
			colIndex++;
		}

		Point temp(static_cast<int>(values[0]), values[1], values[2]);
		result.push_back(temp);
	}

	file.close();

	return result;
}

void visualizeData(Delunay& d, Voronoi& v, Point& p)
{
	std::string fileName = "visualize.txt";

	std::ofstream file;
	file.open(fileName);

	file << "OptimalPoint - Start\n";

	file << p.x << " " << p.y;

	file << "\nOptimalPoint - End\n";

	file << "Circumcenters - Start\n";

	for (auto& triangle : d.borders) {
		file << triangle.circumCenter.x << " " << triangle.circumCenter.y << "\n";
	}

	file << "Circumcenters - End\n";

	file << "Triangles - Start\n";

	for (auto& triangle : d.borders) {
		file << triangle.verticies[0].x << "," << triangle.verticies[0].y << " ";
		file << triangle.verticies[1].x << "," << triangle.verticies[1].y << " ";
		file << triangle.verticies[2].x << "," << triangle.verticies[2].y << "\n";
	}

	file << "Triangles - End\n";

	file << "Edges - Start\n";

	for (auto& edge : v.edges) {
		file << edge.p1.x << "," << edge.p1.y << " " << edge.p2.x << "," << edge.p2.y << "\n";
	}

	file << "Edges - End\n";

	file.close();
}
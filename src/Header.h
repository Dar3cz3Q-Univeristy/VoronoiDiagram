#pragma once
#include "Delunay.h"
#include "Voronoi.h"

std::vector<Point> initializePoints(std::string);
void visualizeData(Delunay&, Voronoi&, Point&, std::vector<Point>&);

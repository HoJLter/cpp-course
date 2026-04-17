#pragma once
#include "Geometry.h"

struct TriangulationResult {
	std::vector<Edge> diagonals;
	float diagonalsLen;
};

class ITriangulator {
public:
	virtual ~ITriangulator() = default;
	virtual TriangulationResult triangulate(const Polygon& poly) = 0;
};

class EarTriangulator : public ITriangulator {
	TriangulationResult triangulate(const Polygon& poly) = 0;
};

class DynamicTriangulator : public ITriangulator {
	TriangulationResult triangulate(const Polygon& poly) = 0;
};
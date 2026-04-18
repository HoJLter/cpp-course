#pragma once
#include "algo/Geometry.h"


enum class TriangulatorType {
	Ear,
	Recursive,
	Dynamic
};

struct TriangulationResult {
	std::vector<Edge> diagonals;
	float diagonalsLen = 0;
};

class ITriangulator {
public:
	virtual ~ITriangulator() = default;
	virtual TriangulationResult triangulate(const Polygon& poly) = 0;
};

class EarTriangulator : public ITriangulator {
private:
	void triangleImpl(const Polygon& poly, TriangulationResult& result);
public:
	TriangulationResult triangulate(const Polygon& poly) override;
};

class RecursiveTriangulator : public ITriangulator {
private:
	void triangleImpl(const Polygon& poly, TriangulationResult& result);
public:
	TriangulationResult triangulate(const Polygon& poly) override;
};	

class DynamicTriangulator : public ITriangulator {
private:
	void triangleImpl(const Polygon& poly, TriangulationResult& result);
public:
	TriangulationResult triangulate(const Polygon& poly) override;
};


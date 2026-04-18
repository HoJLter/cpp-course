#include "algo/Triangulators.h"


void EarTriangulator::triangleImpl(const Polygon& poly, TriangulationResult& result) {
	if (poly.size() == 3) {
		return;
	}
	float minLen = -1;
	Vertex v1 = {};
	Vertex v2 = {};
	int middleEarIndex = -1;
	for (int i = 0; i < poly.size(); i++) {
		int pairId = (i + 2) % poly.size();
		float curLen = calcLen(poly[i], poly[pairId]);
		if (curLen < minLen || minLen == -1) {
			middleEarIndex = (i + 1) % poly.size();
			minLen = curLen;
			v1 = poly[i];
			v2 = poly[pairId];
		}
	}

	result.diagonals.push_back(Edge(v1.id, v2.id));
	result.diagonalsLen += minLen;
	
	Polygon newPoly;
	for (int i = 0; i < poly.size(); i++) {
		if (i != middleEarIndex) {
			newPoly.vertices.push_back(poly[i]);
		}
	}
	triangleImpl(newPoly, result);
}

TriangulationResult EarTriangulator::triangulate(const Polygon& poly) {
	TriangulationResult result;
	triangleImpl(poly, result);
	return result;
}


TriangulationResult DynamicTriangulator::triangulate(const Polygon& poly) {
	TriangulationResult result;
	triangleImpl(poly, result);
	return result;
}

void DynamicTriangulator::triangleImpl(const Polygon& poly, TriangulationResult& result) {
	int len = poly.size();
	if (len == 3) {
		return;
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			bool isNeighbor = (((i + 1) % len == j) || ((i - 1 + len) % len == j) || i == j);
			if (isNeighbor) continue;
			SplittedPoly sp = splitPolygon(poly, Edge(i, j));

			result.diagonals.push_back(Edge(i, j));
			result.diagonalsLen += calcLen(poly[i], poly[j]);
			TriangulationResult resA;
			triangleImpl(sp.a, resA);
			TriangulationResult resB;
			triangleImpl(sp.b,resB);
		}
		
	}

	
}

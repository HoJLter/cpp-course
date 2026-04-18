#include "algo/Triangulators.h"
#include <set>

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




void RecursiveTriangulator::triangleImpl(const Polygon& poly, TriangulationResult& result) {
	bool first = true;
	TriangulationResult best;
	int len = poly.size();
	if (len <= 3) {
		result.diagonalsLen = 0;
		return;
	}
	for (int i = 0; i < len; i++) {
		for (int j = i+1; j < len; j++) {
			bool isNeighbor = (((i + 1) % len == j) || ((i - 1 + len) % len == j) || i == j);
			if (isNeighbor) continue;
			SplittedPoly sp = splitPolygon(poly, Edge(i, j));

			
			TriangulationResult resA;
			triangleImpl(sp.a, resA);
			TriangulationResult resB;
			triangleImpl(sp.b,resB);

			TriangulationResult candidate;
			candidate.diagonalsLen = calcLen(poly[i], poly[j]) + resA.diagonalsLen + resB.diagonalsLen;
			candidate.diagonals.push_back(Edge(poly[i].id, poly[j].id));
			for (const Edge& e : resA.diagonals)
				candidate.diagonals.push_back(e);

			for (const Edge& e : resB.diagonals)
				candidate.diagonals.push_back(e);


			if (first || candidate.diagonalsLen < best.diagonalsLen) {
				best = candidate;
				first = false;
			}
		}
	}
	result = best;
}

TriangulationResult RecursiveTriangulator::triangulate(const Polygon& poly) {
	TriangulationResult result;
	triangleImpl(poly, result);
	return result;
}


TriangulationResult DynamicTriangulator::triangulate(const Polygon& poly) {
	TriangulationResult result;
	triangleImpl(poly, result);
	return result;
}


void addDiagonalUnique(
	TriangulationResult& result,
	std::set<std::pair<int, int>>& used,
	int a, int b
) {
	if (a > b) std::swap(a, b);

	if (used.insert({ a, b }).second) {
		result.diagonals.push_back(Edge(a, b));
	}
}

void restore(int i, int j,
	const Polygon& poly,
	const std::vector<std::vector<int>>& split,
	TriangulationResult& result,
	std::set<std::pair<int, int>>& used) {

	if (j - i <= 2)
		return;

	int k = split[i][j];
	if (k == -1)
		return;

	if (k != i + 1) {
		addDiagonalUnique(result, used, poly[i].id, poly[k].id);
	}

	if (k != j - 1) {
		addDiagonalUnique(result, used, poly[k].id, poly[j].id);
	}

	restore(i, k, poly, split, result, used);
	restore(k, j, poly, split, result, used);
}

void DynamicTriangulator::triangleImpl(const Polygon& poly, TriangulationResult& result) {
	int vCount = poly.size();
	std::vector<std::vector<float>> resultMatrix(
		vCount, std::vector<float>(vCount, 10000.f)
	);
	std::vector<std::vector<int>> splitPoints(
		vCount, std::vector<int>(vCount, -1)
	);


	for (int segmentLen = 0; segmentLen < vCount; segmentLen++) {
		for (int i = 0; i + segmentLen < vCount; i++) {
			int j = i + segmentLen;
			if (segmentLen < 3) {
				resultMatrix[i][j] = 0;
				continue;
			}

			for (int k = i + 1; k < j; ++k) {
				float extra = 0.0f;

				if (k != i + 1)
					extra += calcLen (poly[i], poly[k]);

				if (k != j - 1)
					extra += calcLen(poly[k], poly[j]);

				float candidate = resultMatrix[i][k] + resultMatrix[k][j] + extra;

				if (candidate < resultMatrix[i][j]) {
					resultMatrix[i][j] = candidate;
					splitPoints[i][j] = k;
				}
			}
		}
	}

	result.diagonalsLen = resultMatrix[0][vCount - 1];
	std::set<std::pair<int, int>> used;

	restore(0, vCount - 1, poly, splitPoints, result, used);
}
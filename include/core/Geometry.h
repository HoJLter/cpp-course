#pragma once
#include <vector>

struct Point{
	float x;
	float y;
};

struct Vertex {
	Point a;
	int id;
};

struct Edge {
	int aID;
	int bID;
};

struct Polygon {
	std::vector<Vertex> vertices;

	int size() const { return vertices.size(); }
	Vertex& operator[](int i) { return vertices[i]; }
	const Vertex& operator[](int i) const { return vertices[i]; }
};
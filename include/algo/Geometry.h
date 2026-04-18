#pragma once
#include <vector>
#include "SFML/Graphics.hpp"


struct Vertex {
	Vertex() : x(0), y(0) {};
	Vertex(float a, float b, int i) : x(a), y(b), id(i) {};
	int id;
	float x;
	float y;
};

struct Edge {
	Edge(int i, int j) :aID(i), bID(j) {};

	int aID;
	int bID;
};

struct Polygon{
	std::vector<Vertex> vertices;

	int size() const { return vertices.size(); }
	Vertex& operator[](int i) { return vertices[i]; }
	const Vertex& operator[](int i) const { return vertices[i]; }
};

struct SplittedPoly {
	Polygon a;
	Polygon b;
};

bool isConvex(const Polygon& poly);
float calcLen(const Vertex& a, const Vertex& b);

Polygon vertexArrToPoly(const sf::VertexArray& arr);
sf::VertexArray polyToVertexArr(const Polygon& poly);

SplittedPoly splitPolygon(const Polygon& poly, const Edge& edgeCutter);
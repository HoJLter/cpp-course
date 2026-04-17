#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

struct Point{
	float x;
	float y;
};

struct Vertex {
	Point coords;
	int id;
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


bool isConvex(const Polygon& poly);
float calcLen(const Point& a, const Point& b);

Polygon vertexArrToPoly(const sf::VertexArray& arr);
sf::VertexArray polyToVertexArr(const Polygon& poly);
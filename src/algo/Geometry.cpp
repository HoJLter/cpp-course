#include "algo/Geometry.h"

bool isConvex(const Polygon& poly) {
    int len = poly.size();
    int sign = 0;
    for (int i = 0; i < len; ++i) {
        auto& A = poly[i];
        auto& B = poly[(i + 1) % len];
        auto& C = poly[(i + 2) % len];

        float cross =
            (B.coords.x - A.coords.x) * (C.coords.y - A.coords.y) -
            (B.coords.y - A.coords.y) * (C.coords.x - A.coords.x);

        int signCur = cross > 0 ? 1 : -1;
        if (signCur != sign && sign != 0) {
            return false;
        }
        else {
            sign = signCur;
        }
    }
    return true;
}

float calcLen(const Point& a, const Point& b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

Polygon vertexArrToPoly(const sf::VertexArray& arr) {
    Polygon poly;
    for (int i = 0; i < arr.getVertexCount(); i++) {
        poly.vertices.push_back({arr[i].position.x, arr[i].position.y, i});
    }
    return poly;
}

sf::VertexArray polyToVertexArr(const Polygon& poly) {
    sf::VertexArray arr;
    for (Vertex v : poly.vertices) {
        arr.append(sf::Vertex({ v.coords.x, v.coords.y }));
    }
    return arr;
}
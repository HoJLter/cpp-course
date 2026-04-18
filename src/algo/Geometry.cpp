#include "algo/Geometry.h"

bool isConvex(const Polygon& poly) {
    int len = poly.size();
    int sign = 0;
    for (int i = 0; i < len; ++i) {
        auto& A = poly[i];
        auto& B = poly[(i + 1) % len];
        auto& C = poly[(i + 2) % len];

        float cross =
            (B.x - A.x) * (C.y - A.y) -
            (B.y - A.y) * (C.x - A.x);

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

float calcLen(const Vertex& a, const Vertex& b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

Polygon vertexArrToPoly(const sf::VertexArray& arr) {
    Polygon poly;
    for (int i = 0; i < arr.getVertexCount(); i++) {
        poly.vertices.push_back(Vertex(arr[i].position.x, arr[i].position.y, i));
    }
    return poly;
}

sf::VertexArray polyToVertexArr(const Polygon& poly) {
    sf::VertexArray arr;
    for (Vertex v : poly.vertices) {
        arr.append(sf::Vertex({ v.x, v.y }));
    }
    return arr;
}


SplittedPoly splitPolygon(const Polygon& poly, const Edge& edgeCutter) {
    SplittedPoly result;
    int a = edgeCutter.aID > edgeCutter.bID ? edgeCutter.aID : edgeCutter.bID;
    int b = edgeCutter.aID < edgeCutter.bID ? edgeCutter.aID : edgeCutter.bID;

    for (int i = 0; i < poly.size(); i++) {
        if (i > a && i < b) {
            result.a.vertices.push_back(poly[i]);
        }
        else if (i < a || i > b) {
            result.b.vertices.push_back(poly[i]);
        }
        else {
            result.a.vertices.push_back(poly[i]);
            result.b.vertices.push_back(poly[i]);
        }
    }
    return result;
}

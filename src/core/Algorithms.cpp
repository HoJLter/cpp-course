#include "SFML/Graphics.hpp"
#include "utils/Log.h"
#include <limits>
#include <set>


bool isConvex(sf::VertexArray dots, int len) {
    int sign = 0;
    for (int i = 0; i < len; ++i) {
        auto& A = dots[i].position;
        auto& B = dots[(i + 1) % len].position;
        auto& C = dots[(i + 2) % len].position;

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

float calcLen(sf::Vector2f a, sf::Vector2f b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

struct Diagonal {
    int a;
    int b;

    Diagonal(int i, int j) {
        a = std::min(i, j);
        b = std::max(i, j);
    }

    bool operator<(const Diagonal& other) const {
        if (a != other.a) return a < other.a;
        else return b < other.b;
    }
};

void calcLossLenDia(const sf::VertexArray& dots, sf::VertexArray& diaArr, float& lenSum) {

    int len = dots.getVertexCount();
    std::set<Diagonal> usedDiagonals;
    for (int i = 0; i < len; i++) {
        float minLen = 10000000.f;
        sf::Vertex v1;
        sf::Vertex v2;
        int index = -1;
        for (int j = 0; j < len; j++) {
            bool isNeighbor = (j == (i + 1) % len || j == (i - 1 + len) % len || i == j);
            if (isNeighbor || usedDiagonals.count(Diagonal(i, j))) continue;
            float curLen = calcLen(dots[i].position, dots[j].position);
            if (minLen > curLen) {
                minLen = curLen;
                v1 = dots[i];
                v2 = dots[j];
                index = j;
            }
        }
        if (index != -1) {
            diaArr.append(dots[i]);
            diaArr.append(dots[index]);
            lenSum += minLen;
            usedDiagonals.insert(Diagonal(i, index));
        }
    }
}
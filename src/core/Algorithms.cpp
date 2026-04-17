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

//void calcLossLenDia(const sf::VertexArray& dots, sf::VertexArray& diaArr, float& lenSum) {
//
//    int len = dots.getVertexCount();
//    std::set<Diagonal> usedDiagonals;
//    for (int i = 0; i < len; i++) {
//        float minLen = 10000000.f;
//        sf::Vertex v1;
//        sf::Vertex v2;
//        int index = -1;
//        for (int j = 0; j < len; j++) {
//            bool isNeighbor = (j == (i + 1) % len || j == (i - 1 + len) % len || i == j);
//            if (isNeighbor || usedDiagonals.count(Diagonal(i, j))) continue;
//            float curLen = calcLen(dots[i].position, dots[j].position);
//            if (minLen > curLen) {
//                minLen = curLen;
//                v1 = dots[i];
//                v2 = dots[j];
//                index = j;
//            }
//        }
//        if (index != -1) {
//            diaArr.append(dots[i]);
//            diaArr.append(dots[index]);
//            lenSum += minLen;
//            usedDiagonals.insert(Diagonal(i, index));
//        }
//    }
//}


//концепт:
//перебираем все "уши", строим треугольник, рассматриваем новую фигуру
void lossLenEar(const sf::VertexArray& dots, sf::VertexArray& diaArr, float& lenSum) {
    int dotCount = dots.getVertexCount();
    if (dotCount == 3) return;

    sf::Vertex a;
    sf::Vertex b;
    int minLen = -1;
    int index = -1;
    for (int i = 0; i < dotCount; i++) {
        Log::debug(std::to_string(i) + " " + std::to_string((i + 2) % dotCount));
        float curLen = calcLen(dots[i].position, dots[(i + 2) % dotCount].position);
        if (curLen < minLen || minLen == -1) {
            minLen = curLen;
            a = dots[i];
            b = dots[(i + 2) % dotCount];
            index = i;
        }
    }
    lenSum += minLen;
    diaArr.append(a);
    diaArr.append(b);
    lossLenEar(dots., diaArr, lenSum);
};

// dots - input
// diaArr, lenSum - output
void calcLossLenDia(const sf::VertexArray& dots, sf::VertexArray& diaArr, float& lenSum) {
    lossLenEar(dots, diaArr, lenSum);
}


#pragma once
#include <vector>
#include <cmath>
#include "SFML/Graphics.hpp"


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

struct DiagonalData {
    sf::VertexArray diaDots;
    float lenSum = 0;
};

DiagonalData calcLossLenDia(sf::VertexArray dots, int len) {
    DiagonalData dia;

    struct diaInfo {
        int i;
        int j;
        float len;
    };
    for (int i = 0; i < len; ++i) {
        float min = calcLen(dots[i].position, dots[0].position);
        diaInfo minDia;
        for (int j = 0; j < len; ++j) {
            bool isNeighbor = ((j == i + 1 % len) || (j == (i - 1 + len) % len));
            if (isNeighbor) {
                continue;
            }
            float curLen = calcLen(dots[i].position, dots[j].position);
            if (min > curLen) {
                min = curLen;
                minDia = { i, j, curLen };
            }
            
        }
        dia.diaDots.append(dots[minDia.i]);
        dia.diaDots.append(dots[minDia.j]);
        dia.lenSum += minDia.len;
    }
    return dia;
}
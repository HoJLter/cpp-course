#pragma once
#include <vector>
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
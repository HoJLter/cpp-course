#pragma once
#include <vector>
#include <cmath>
#include "SFML/Graphics.hpp"


bool isConvex(sf::VertexArray dots, int len);

float calcLen(sf::Vector2f a, sf::Vector2f b);

//следущий - (i+1)%len
//предыдущий - (i-1+len)%len

struct DiaData {
    sf::Vector2<sf::VertexArray> coords;
    float len;
};

void calcLossLenDia(const sf::VertexArray& dots, sf::VertexArray& diaArr, float& lenSum);
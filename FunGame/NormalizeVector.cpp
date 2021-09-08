#include "NormalizeVector.h"

#include <cmath>

sf::Vector2f NormalizeVector::Normalize(const sf::Vector2f& vectorToNormalize)
{
    // Sqrt(a^2 + b^2)
    float length = sqrt((vectorToNormalize.x * vectorToNormalize.x) + (vectorToNormalize.y * vectorToNormalize.y));
    if (length != 0) {
        return sf::Vector2f(vectorToNormalize.x / length, vectorToNormalize.y / length);
    }
    else {
        return vectorToNormalize;
    }
}

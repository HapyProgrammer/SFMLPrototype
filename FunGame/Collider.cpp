#include "Collider.h"

#include <SFML/Graphics.hpp>

Collider::Collider(sf::RectangleShape& body) :
    body(body)
{

}

Collider::~Collider()
{
}

// AABB Collision detection
bool Collider::CheckCollision(Collider& other, float priority)
{
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    // Find out how far they intersect within each other
    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.f && intersectY < 0.f) {
        // See how heavy this object is
        priority = std::min(std::max(priority, 0.f), 1.f);

        // Push out from X axis
        if (intersectX > intersectY) {
            if (deltaX > 0.f) {
                Move(intersectX * (1.f - priority), 0.f);
                other.Move((-intersectX * priority), 0.f);
            }
            else {
                Move(-intersectX * (1.f - priority), 0.f);
                other.Move((intersectX * priority), 0.f);
            }
        }
        // Push out from Y axis
        else {
            if (deltaY > 0.f) {
                Move(0.f ,intersectY * (1.f - priority));
                other.Move(0.f, (-intersectY * priority));
            }
            else {
                Move(0.f, -intersectY * (1.f - priority));
                other.Move(0.f, (intersectY * priority));
            }
        }
        return true;
    }
    return false;
}

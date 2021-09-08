#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	void Move(float dx, float dy) {  body.move(dx, dy); } // Push objects outside of each other

	bool CheckCollision(Collider& other, float priority);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.f; }

private:
	sf::RectangleShape& body;
};


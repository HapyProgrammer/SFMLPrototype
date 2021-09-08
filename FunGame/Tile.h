#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Tile
{
public:
	Tile(sf::Vector2f size, sf::Vector2f position);
	~Tile();

	void Render(sf::RenderWindow& target);
	Collider GetCollider(){ return Collider(tileColliderBox); }

private:
	sf::RectangleShape tileColliderBox;

};


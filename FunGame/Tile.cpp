#include "Tile.h"

Tile::Tile(sf::Vector2f size, sf::Vector2f position)
{
	tileColliderBox.setSize(size);
	tileColliderBox.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	tileColliderBox.setPosition(position);

	// Collider debug
	/*tileColliderBox.setOutlineColor(sf::Color::Green);
	tileColliderBox.setOutlineThickness(2.f);
	tileColliderBox.setFillColor(sf::Color::Transparent);*/
}

Tile::~Tile()
{
}

void Tile::Render(sf::RenderWindow& target)
{
	// Draw collider debug
	//target.draw(tileColliderBox);
}

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "WorldSettings.h"

class TileMap : public sf::Drawable, public sf::Transformable
{
public: 
	bool Load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

	std::vector<Tile> groundTiles;
	std::vector<Tile> wallTiles;

private:
	WorldSettings world;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture m_tileset;
	sf::VertexArray m_vertices;

};


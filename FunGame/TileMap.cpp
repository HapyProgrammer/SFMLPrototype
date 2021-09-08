#include "TileMap.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

bool TileMap::Load(const std::string & tileset, sf::Vector2u tileSize, const int * tiles, unsigned int width, unsigned int height)
{
	// Load tile set from files
	if (!m_tileset.loadFromFile(tileset)) {
		return false;
	}

	// Resize vertex array
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize((double)width * height * 4);

	for (unsigned int x = 0; x < width; ++x) {
		for (unsigned int y = 0; y < height; ++y) {

			// Get tile number from level
			int tileNumber = tiles[x + y * width];

			if (tileNumber != 0) {
				// Find the position in tileset texture
				int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
				int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

				// Pointer to current tile quad
				sf::Vertex* quad = &m_vertices[((double)x + (double)y * width) * 4];

				if (quad == nullptr) {
					// Could not get verticies
					return false;
				}

				// Define 4 corners
				quad[0].position = sf::Vector2f(x * tileSize.x,y * tileSize.y);
				quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
				quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

				// Define 4 texture coords
				quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

				// Generate tile collision
				// Due to tile origin being at the center we must offset the position by half a tile in x and y
				Tile mapTile(sf::Vector2f(tileSize.x, tileSize.y), sf::Vector2f(x * tileSize.x + tileSize.x / 2, y * tileSize.y + tileSize.y / 2));

				// If tile is not a wall set as a ground tile
				tileNumber <= 9 ? groundTiles.push_back(mapTile) : wallTiles.push_back(mapTile);
			}
		}
	}
	return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply the transform
	states.transform *= getTransform();

	// Apply the tileset texture
	states.texture = &m_tileset;

	// Draw the vertex array
	target.draw(m_vertices, states);
}

#pragma once
#include <SFML/Graphics.hpp>

class WorldSettings
{
public:
	const float gravity = 10.f;
	const float delayBetweenEnemySpawn = 1.5f;
	const int tileSize = 32;
	const int worldWidth = 44;
	const int worldHeight = 14;
};


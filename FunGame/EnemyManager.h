#pragma once
#include <SFML/Graphics.hpp>
#include "EnemyBlob.h"
class EnemyManager
{
public:

	void spawnEnemy(std::shared_ptr<sf::Texture> texture);

	std::vector<EnemyBlob> enemies;

};


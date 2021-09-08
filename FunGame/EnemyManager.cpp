#include "EnemyManager.h"

void EnemyManager::spawnEnemy(std::shared_ptr<sf::Texture> texture)
{
	// Get random number between 100 - 900
	float randomSpawnX = rand() % 900 + 100;

	// If no enemies then spawn one
	if (enemies.empty()) {
		EnemyBlob enemy(sf::Vector2f(randomSpawnX, 0.f), texture);
		enemies.push_back(enemy);
	}
	else {
		// Check if there is an enemy that is !bIsEnabled
		for (int i = 0; i < enemies.size(); i++) {
			if (!enemies[i].bIsEnabled) {
				enemies[i].Respawn(sf::Vector2f(randomSpawnX, 0.f));
				return;
			}
		}

		// If not just spawn another one
		EnemyBlob enemy(sf::Vector2f(randomSpawnX, 0.f), texture);
		enemies.push_back(enemy);
	}
}

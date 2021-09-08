#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Entity.h"
#include "WorldSettings.h"

class EnemyBlob : public Entity
{
public:
	EnemyBlob(sf::Vector2f position, std::shared_ptr<sf::Texture> texture);
	~EnemyBlob();

	float enemyMovementSpeed = 15.f;
	float enemyScale = 2.f;
	unsigned int patrolDistance = 10;

private:
	void Movement(float deltaTime) override;
};


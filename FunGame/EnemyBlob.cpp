#include "EnemyBlob.h"

#include <cmath>
#include <iostream>
#include "Entity.h"

EnemyBlob::EnemyBlob(sf::Vector2f position, std::shared_ptr<sf::Texture> texture)
{
	colliderBox.setPosition(position);

	sprite.setTexture(*texture);
	spriteHeight = 13;
	spriteWidth = 16;
	spriteScale = 2.f;

	bHasAnimation = true;
	bHasGravity = true;
	bIsCurrentlyMoving = true;

	InitShape(sf::Color::Red);
}

EnemyBlob::~EnemyBlob()
{
}

void EnemyBlob::Movement(float deltaTime)
{
	// Move back and forth using sin
	timeElapsedInSeconds += deltaTime;
	float currentPosition = sin(timeElapsedInSeconds) * patrolDistance * enemyMovementSpeed * deltaTime;
	currentPosition < 0 ? sprite.setScale(sf::Vector2f(spriteScale, spriteScale)) : sprite.setScale(sf::Vector2f(-spriteScale, spriteScale));

	// Reset timer after above 2PI to prevent the number getting too large
	if (timeElapsedInSeconds >= 6.3) {
		timeElapsedInSeconds = 0;
	}
	colliderBox.move(currentPosition, 0.f);
}


#define _USE_MATH_DEFINES
#include "Player.h"

#include <cmath>
#include <iostream>
#include "NormalizeVector.h"
#include "Projectile.h"

Player::Player(sf::Vector2f position)
{
	colliderBox.setPosition(position);

	if (!playerTexture.loadFromFile("resources/Player.png")) {
		std::cout << "cant find player sprite in player class" << std::endl;
		return;
	}
	sprite.setTexture(playerTexture);
	spriteWidth = 24;
	spriteHeight = 30;
	spriteScale = 2.f;

	bHasAnimation = true;
	bHasGravity = true;
	bHasInput = true;

	projectileSpawnOffset = sf::Vector2f(spriteWidth / 2, 0);

	InitShape(sf::Color::Blue);
}

Player::~Player()
{
}

void Player::ResetGame()
{
	bIsEnabled = true;
}

// UPDATE //

void Player::UpdateInput(float deltaTime, sf::Vector2f mousePosition)
{
	// Input
	if (bIsEnabled) {
		// Movement
		float movement = sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? -1 : 
							sf::Keyboard::isKeyPressed(sf::Keyboard::D) ? 1 : 0;

		colliderBox.move(playerMovementSpeed * movement, 0.f);
		movement == 0 ? sprite.setScale(sprite.getScale()) : sprite.setScale(sf::Vector2f(spriteScale * movement, spriteScale));
		bIsCurrentlyMoving = movement;

		// Jump
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && bIsGrounded) {
			currentYVelocity = jumpInitialYVelocity;
			bIsGrounded = false;
		}

		// Fire Projectile
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bCanFire) {
			projectileCooldownTimer = 0;
			bCanFire = false;
			FireProjectile(mousePosition);
		}
		else {
			if (projectileCooldownTimer < delayBetweenProjectile) {
				projectileCooldownTimer += deltaTime;
			}
			else {
				bCanFire = true;
			}
		}
	}
	else {
		// Reset game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			ResetGame();
		}
	}
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	UpdateInput(deltaTime, mousePosition);
}

// Projectile // 

void Player::FireProjectile(sf::Vector2f mousePosition)
{
	// If there is no projectiles spawn one
	if (projectilePool.empty()) {
		Projectile projectile(colliderBox.getPosition() + projectileSpawnOffset, projectileTexture, GetFiringAngle(mousePosition), projectileSpeed);
		projectilePool.push_back(projectile);
	}
	else {
		// Check if there is a projectile that exists and is !bIsEnabled
		for (int i = 0; i < projectilePool.size(); i++) {
			if (!projectilePool[i].bIsEnabled) {
				projectilePool[i].SpawnProjectile(colliderBox.getPosition() + projectileSpawnOffset, GetFiringAngle(mousePosition), projectileSpeed);
				return ;
			}
		}
		// If not just spawn another one
		Projectile spawnedProjectile(colliderBox.getPosition() + projectileSpawnOffset, projectileTexture, GetFiringAngle(mousePosition), projectileSpeed);
		projectilePool.push_back(spawnedProjectile);
	}
}

float Player::GetFiringAngle(sf::Vector2f mousePosition)
{
	// Get normalized direction
	sf::Vector2f playerPosition = colliderBox.getPosition();
	sf::Vector2f direction = mousePosition - playerPosition;
	sf::Vector2f normalisedVector = NormalizeVector::Normalize(direction);

	// Convert vector to angle in degrees
	float angleInRadians = std::atan2(normalisedVector.y, normalisedVector.x);
	float angleInDegrees = (angleInRadians / M_PI) * 180.0;
	if (angleInDegrees < 0) {
		angleInDegrees += 360;
	}

	return angleInDegrees;
}



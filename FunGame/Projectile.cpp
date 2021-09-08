#define _USE_MATH_DEFINES
#define DEGREES_TO_RADIANS ((2*M_PI) / 360)
#include "Projectile.h"

#include <cmath>
#include <iostream>
#include "NormalizeVector.h"
#include "WorldSettings.h"

Projectile::Projectile(sf::Vector2f position, std::shared_ptr<sf::Texture> texture, float angle, float speed)
{
	colliderBox.setRotation(angle);
	colliderBox.setPosition(position);

	sprite.setTexture(*texture);
	spriteWidth = 9;
	spriteHeight = 7;
	spriteScale = 2.f;

	bHasGravity = true;

	projectileSpeed = speed;

	// Set velocities via projectile speed and angle
	currentYVelocity = sin(DEGREES_TO_RADIANS * angle) * projectileSpeed;
	xVelocity = cos(DEGREES_TO_RADIANS * angle) * projectileSpeed;

	InitShape(sf::Color::Blue);
}

Projectile::~Projectile()
{
}

// Angle and speed is needed to respawn
void Projectile::SpawnProjectile(sf::Vector2f position, float angle, float speed)
{
	// Reset variables to new angle and speed
	colliderBox.setRotation(angle);
	colliderBox.setPosition(position);
	bIsEnabled = true;
	timeElapsedInSeconds = 0;
	projectileSpeed = speed;
	currentYVelocity = sin(DEGREES_TO_RADIANS * angle) * projectileSpeed;
	xVelocity = cos(DEGREES_TO_RADIANS * angle) * projectileSpeed;
}

void Projectile::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	if (bIsEnabled) {
		if (timeElapsedInSeconds >= projectileLifetime) {
			bIsEnabled = false;
		}
		sprite.setRotation(colliderBox.getRotation());
	}
}

void Projectile::UpdateGravity(float gravityStrength, float deltaTime)
{
	Entity::UpdateGravity(gravityStrength, deltaTime);

	// Get normalised direction of current velocity
	sf::Vector2f normalizedVelocity = NormalizeVector::Normalize(sf::Vector2f(xVelocity, currentYVelocity));
	float lookAtAngle = (abs(normalizedVelocity.y)) * 90;

	// Set collider rotation to the correct angle
	lookAtAngle = xVelocity >= 0 ? 
					currentYVelocity >= 0 ? lookAtAngle : 360 - lookAtAngle : 
					currentYVelocity >= 0 ? 180 - lookAtAngle : 180 + lookAtAngle;
	
	colliderBox.setRotation(lookAtAngle);
}

void Projectile::Movement(float deltaTime)
{
	colliderBox.move(xVelocity, 0);
}



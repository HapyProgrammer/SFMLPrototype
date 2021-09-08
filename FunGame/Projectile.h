#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Entity.h"
#include "WorldSettings.h"

class Projectile : public Entity
{
public:
	Projectile(sf::Vector2f position, std::shared_ptr<sf::Texture> texture, float angle, float speed);
	~Projectile();

	void Update(float deltaTime) override;
	void SpawnProjectile(sf::Vector2f position, float angle, float speed);
	void UpdateGravity(float gravityStrength, float deltaTime) override;
	void Movement(float deltaTime) override;

	float projectileScale = 2.f;
	float projectileSpeed = 2.f;
	float projectileLifetime = 2.f;

private:
	float xVelocity = 0;

};


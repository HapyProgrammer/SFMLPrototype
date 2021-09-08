#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Entity.h"
#include "Projectile.h"
#include "WorldSettings.h"

class Player : public Entity
{
public:
	Player(sf::Vector2f position);
	~Player();

	void Update(float deltaTime) override;

	std::vector<Projectile> projectilePool;
	std::shared_ptr<sf::Texture> projectileTexture;

	sf::Vector2f mousePosition;

	float playerMovementSpeed = 10.f;
	float jumpInitialYVelocity = -5.f;
	float projectileSpeed = 10.f;

private:
	void UpdateInput(float deltaTime, sf::Vector2f mousePosition);

	void FireProjectile(sf::Vector2f mousePosition);
	float GetFiringAngle(sf::Vector2f mousePosition);

	void ResetGame();

	// Player settings
	sf::Texture playerTexture;
	WorldSettings worldSetting;

	sf::Vector2f projectileSpawnOffset;

	bool bCanFire = true;
	
	float delayBetweenProjectile = 0.5f;
	float projectileCooldownTimer = 0;
};

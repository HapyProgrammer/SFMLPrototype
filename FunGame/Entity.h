#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "WorldSettings.h"

class Entity
{
public:
	void InitShape(sf::Color colliderBoxColor);

	virtual void Update(float deltaTime);
	void UpdateAnimation(float deltaTime);
	virtual void UpdateGravity(float gravityStrength, float deltaTime);
	virtual void Movement(float deltaTime) {};

	void Render(sf::RenderTarget& target);

	virtual void Respawn(sf::Vector2f position);

	sf::Sprite sprite;
	sf::RectangleShape colliderBox;
	sf::Texture spriteTexture;

	WorldSettings worldSetting;
	Collider GetCollider() { return Collider(colliderBox); }

	bool bIsGrounded = false;
	bool bIsEnabled = true;
	bool bIsCurrentlyMoving = false;

	bool bHasAnimation = false;
	bool bHasGravity = false;
	bool bHasInput = false;

	unsigned int spriteWidth = 32;
	unsigned int spriteHeight = 32;
	float spriteScale = 1.f;

	unsigned int currentAnimation = 0;
	unsigned int walkAnimationEnd = 3;
	float animationDelayInSeconds = 0.05f; // 3 frame delay
	float currentAnimationTime = 0.f;
	float currentYVelocity = 0.f;

	float timeElapsedInSeconds = 0;
};


#include "Entity.h"

// Initialize //

void Entity::InitShape(sf::Color colliderBoxColor)
{
	// Create sprite
	sprite.setOrigin(spriteWidth / 2, spriteHeight / 2);
	sprite.setScale(sf::Vector2f(spriteScale, spriteScale));

	// Create hitbox
	colliderBox.setSize(sf::Vector2f(spriteWidth * spriteScale, spriteHeight * spriteScale));
	colliderBox.setOrigin(colliderBox.getSize().x / 2, colliderBox.getSize().y / 2);

	// Collider debug
	colliderBox.setOutlineColor(colliderBoxColor);
	colliderBox.setOutlineThickness(2.f);
	colliderBox.setFillColor(sf::Color::Transparent);
}

void Entity::Respawn(sf::Vector2f position)
{
	// Reset values
	colliderBox.setPosition(position);
	bIsEnabled = true;
	bIsGrounded = false;
	currentYVelocity = 0;
	timeElapsedInSeconds = 0;
}

// Update //

void Entity::UpdateAnimation(float deltaTime)
{
	// Add delay between frames
	if (bIsCurrentlyMoving) {
		currentAnimationTime += deltaTime;
		if (currentAnimationTime > animationDelayInSeconds) {
			currentAnimationTime = 0;
			currentAnimation++;
			if (currentAnimation >= walkAnimationEnd) {
				currentAnimation = 0;
			}
		}
	}

	// Adjust texture rect to get the right frame of animation
	sprite.setTextureRect(sf::IntRect(currentAnimation * spriteWidth, 0, spriteWidth, spriteHeight));
}

void Entity::UpdateGravity(float gravityStrength, float deltaTime)
{
	if (!bIsGrounded) {
		currentYVelocity += gravityStrength * deltaTime;
		colliderBox.move(0, currentYVelocity);
	}
}

void Entity::Update(float deltaTime)
{
	if (bIsEnabled) {
		if (!bHasInput) { Movement(deltaTime); }
		if (bHasAnimation) { UpdateAnimation(deltaTime); }
		if (bHasGravity) { UpdateGravity(worldSetting.gravity, deltaTime); }
		sprite.setPosition(colliderBox.getPosition());
	}
}
// Render //

void Entity::Render(sf::RenderTarget& target)
{
	if (bIsEnabled) {
		target.draw(sprite);

		// Draw debug
		//target.draw(colliderBox);
	}
}

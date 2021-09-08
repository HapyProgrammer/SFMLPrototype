#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Collider.h"
#include "EnemyBlob.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Projectile.h"
#include "Tile.h"
#include "TileMap.h"
#include "WorldSettings.h"

int main()
{
	srand(time(NULL));
	// Render game
	sf::RenderWindow window(sf::VideoMode(1024, 448), "Fun Game");
	window.setFramerateLimit(60);

	// Set level (Can try to automate this process using image and reading each pixel on image)
	const int level[] =
	{
		10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,
		10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,
		10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,
		10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,
		10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,
		10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,
		10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,
		10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,
		10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,
		10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,
		10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,
		10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,
		 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,
		 4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6
	};

	// Get world settings
	WorldSettings world;

	// Get and set background texture
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("resources/Background.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite background(backgroundTexture);

	// Make tile map
	TileMap map;
	if (!map.Load("resources/Ground.png", sf::Vector2u(world.tileSize, world.tileSize), level, world.worldWidth, world.worldHeight)) {
		return EXIT_FAILURE;
	}

	// Enemies
	sf::Texture enemyTexture;
	if (!enemyTexture.loadFromFile("resources/Enemy.png")) {
		return EXIT_FAILURE;
	}
	std::shared_ptr<sf::Texture> enemyTexturePointer = std::make_shared<sf::Texture>(enemyTexture);

	EnemyManager enemyManager;

	// Get and set player
	sf::Texture projectileTexture;
	if (!projectileTexture.loadFromFile("resources/Projectile.png")) {
		return EXIT_FAILURE;
	}
	std::shared_ptr<sf::Texture> projectileTexturePointer = std::make_shared<sf::Texture>(projectileTexture);

	Player player(sf::Vector2f(100.f, 354.f));
	player.projectileTexture = projectileTexturePointer;

	// Font
	sf::Font gameFont;
	if (!gameFont.loadFromFile("resources/Roboto-BlackItalic.ttf")) {
		return EXIT_FAILURE;
	}
	std::shared_ptr<sf::Font> gameFontPointer = std::make_shared<sf::Font>(gameFont);

	// Score Text
	sf::Text score;
	score.setFont(*gameFontPointer);
	score.setPosition(sf::Vector2f(700, 200));
	score.setOrigin(sf::Vector2f(32, 32));
	score.setCharacterSize(64);

	int scoreNumber = 0;
	float minScoreScale = 1.f;
	float maxScorseScale = 1.2f;
	float scoreShrinkSpeed = 1.f;

	// Game over text
	sf::Text gameOver;
	gameOver.setFont(*gameFontPointer);
	gameOver.setCharacterSize(64);
	gameOver.setOrigin(sf::Vector2f(256.f, 64.f));
	gameOver.setOutlineColor(sf::Color::Black);
	gameOver.setOutlineThickness(1.f);

	bool gameEnded = false;

	// Set clock for delta time
	sf::Clock deltaClock;

	// Set world view to follow player
	sf::View playerView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

	// Set timer at 2 to instantly spawn enemy
	float timer = 2;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Reset game //

		if (gameEnded && player.bIsEnabled) {
			gameEnded = false;
			// Reset player
			player.colliderBox.setPosition(sf::Vector2f(100.f, 354.f));
			if (!player.projectilePool.empty()) {
				for (int i = 0; i < player.projectilePool.size(); i++) {
					player.projectilePool[i].bIsEnabled = false;
				}
			}

			// Reset enemies
			if (!enemyManager.enemies.empty()) {
				for (int i = 0; i < enemyManager.enemies.size(); i++) {
					enemyManager.enemies[i].bIsEnabled = false;
				}
			}

			// Reset score
			scoreNumber = 0;

			// Reset timer
			timer = 2;
		}

		// Collision Events //

		if (player.bIsEnabled) {
			// Player
			Collider playerCollider = player.GetCollider();
			if (!player.bIsGrounded)
			{
				// Player Collision with ground
				for (Tile mapTile : map.groundTiles) {
					if (mapTile.GetCollider().CheckCollision(playerCollider, 1.f)) {
						player.bIsGrounded = true;
					}
				}
			}

			// Player Collision with wall
			for (Tile mapTile : map.wallTiles) {
				mapTile.GetCollider().CheckCollision(playerCollider, 1.f);
			}

			// Projectile Collision with ground
			if (!player.projectilePool.empty()) {
				for (int i = 0; i < player.projectilePool.size(); i++) {
					for (Tile mapTile : map.groundTiles) {
						Collider mapTileCollider = mapTile.GetCollider();
						if (player.projectilePool[i].GetCollider().CheckCollision(mapTileCollider, 1.f)) {
							player.projectilePool[i].bIsEnabled = false;
						}
					}
				}
			}

			// Enemy
			if (!enemyManager.enemies.empty()) {
				for (int i = 0; i < enemyManager.enemies.size(); i++) {
					if (enemyManager.enemies[i].bIsEnabled)
					{
						// Get enemy collider
						Collider enemyBlobCollider = enemyManager.enemies[i].GetCollider();

						// Wall Collisions with Enemy
						for (Tile mapTile : map.wallTiles) {
							mapTile.GetCollider().CheckCollision(enemyBlobCollider, 1.f);
						}

						// Ground Collisions with Enemy
						if (!enemyManager.enemies[i].bIsGrounded) {
							for (Tile mapTile : map.groundTiles) {
								if (mapTile.GetCollider().CheckCollision(enemyBlobCollider, 1.f)) {
									enemyManager.enemies[i].bIsGrounded = true;
								}
							}
						}

						// Player Collisions with Enemy
						if(enemyManager.enemies[i].GetCollider().CheckCollision(playerCollider, 0.5f)) {
							player.bIsEnabled = false;
						}

						// Projectile Collisions with Enemy
						if (!player.projectilePool.empty()) {
							for (int j = 0; j < player.projectilePool.size(); j++) {
								if (player.projectilePool[j].bIsEnabled && player.projectilePool[j].GetCollider().CheckCollision(enemyBlobCollider, 0.f)) {
									scoreNumber++;
									score.setScale(sf::Vector2f(maxScorseScale, maxScorseScale));
									enemyManager.enemies[i].bIsEnabled = false;
									player.projectilePool[j].bIsEnabled = false;
								}
							}
						}
					}
				}
			}
		}

		// Update Events //

		float deltaTime = deltaClock.restart().asSeconds();
		timer += deltaTime;

		// Mouse
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mouseToWorldPos = window.mapPixelToCoords(mousePos);
		player.mousePosition = mouseToWorldPos;

		// Dynamic Text
		float currentScoreScale = score.getScale().x;
		if (currentScoreScale > minScoreScale) {
			currentScoreScale -= deltaTime * scoreShrinkSpeed;
			score.setScale(sf::Vector2f(currentScoreScale, currentScoreScale));
		}
		else { 
			score.setScale(sf::Vector2f(minScoreScale, minScoreScale));
		}
		

		// Player Update
		player.Update(deltaTime);

		if (player.bIsEnabled) {

			// Enemy Spawner
			if (timer > world.delayBetweenEnemySpawn) {
				enemyManager.spawnEnemy(enemyTexturePointer);
				timer = 0;
			}

			// Enemies
			if (!enemyManager.enemies.empty()) {
				for (int i = 0; i < enemyManager.enemies.size(); i++) {
					enemyManager.enemies[i].Update(deltaTime);
				}
			}

			// Player Projectiles
			if (!player.projectilePool.empty()) {
				for (int i = 0; i < player.projectilePool.size(); i++) {
					player.projectilePool[i].Update(deltaTime);
				}
			}
		}


		// Camera //

		playerView.setCenter(player.colliderBox.getPosition().x, playerView.getCenter().y);
		window.setView(playerView);

		// Display //

		// Background
		window.clear(sf::Color(34,32,52,255));
		window.draw(background);
		window.draw(map);

		// Player
		player.Render(window);
		if (!player.projectilePool.empty()) {
			for (int i = 0; i < player.projectilePool.size(); i++) {
				player.projectilePool[i].Render(window);
			}
		}

		// Enemies
		if (!enemyManager.enemies.empty()) {
			for (int i = 0; i < enemyManager.enemies.size(); i++) {
				enemyManager.enemies[i].Render(window);
			}
		}

		// Map collisions
		for (Tile mapTile : map.groundTiles) {
			mapTile.Render(window);
		}
		for (Tile mapTile : map.wallTiles) {
			mapTile.Render(window);
		}

		// UI //

		// Score
		score.setString(std::to_string(scoreNumber));
		window.draw(score);

		// GameOver
		if (!player.bIsEnabled) {
			window.draw(gameOver);
			gameEnded = true;
		}
		else {
			gameOver.setString("Press 'R' to reset\n Score: " + std::to_string(scoreNumber));
			gameOver.setPosition(player.colliderBox.getPosition());
		}

		window.display();
	}

	return 0;
}
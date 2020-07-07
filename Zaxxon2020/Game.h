#pragma once
#ifndef GAME_H
#define GAME_H

#include "Bullet.h"
#include "EnemyBullet.h"

const int mWindowsHeight = 800;
const int mWindowsWidth = 1000;
const sf::String gameTitle = "Zaxxon 2020";

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	static const float playerXSpeed;
	static const float playerYSpeed;
	float viewSpeed;
	static const float zoom;
	static const float zMax;
	static const float bulletSpeed;
	static const float enemySpeed;
	static const float maxY;
	bool playerIsMovingUp;
	bool playerIsMovingLeft;
	bool playerIsMovingRight;
	bool playerIsMovingDown;
	float xMax;

	bool paused;
	sf::Vector2f startPos;
	sf::Vector2f viewVector;
	sf::Vector2f bulletVector;

	bool dead = false;
	

	sf::RenderWindow mWindow;
	sf::View view;

	std::vector<std::shared_ptr<Entity>> m_Entities;
	std::vector<std::shared_ptr<Bullet>> m_bullets;
	std::vector<std::shared_ptr<EnemyBullet>> m_enemyBullets;
	std::shared_ptr<Entity> player;
	std::shared_ptr<Entity> enemy;

	sf::Texture playerTexture;
	sf::Texture tWallTexture;
	sf::Texture enemyTexture;
	sf::Texture playerBulletTexture;
	sf::Texture shadowTexture;
	sf::Texture enemyWeaponTexture;
private:
	void initWindow();
	void initSprites();
	void initView();
	void initTextures();
	void resetGame();

	void resetPlayer();
	void initPlayer();

	void initEnemy();
	void manageEnemy(sf::Time elapsedTime);
	void resetEnemy();

	void initPlayerBullet();
	void initEnemyBullet();

	void handleGameOver();

	void updatePlayer(sf::Time elapsedTime);
	void render(sf::Time elapsedTime);
	void renderSlider();
	void renderShadow();
	void renderFloor();
	void manageBullets(sf::Time elapsedTime);
	void resetBullets();
	void manageEnemyBullets(sf::Time elapsedTime);
	void resetEnemyBullets();
	void manageCollisions();

	void processEvents();
	void handleInput(sf::Keyboard::Key key, bool pressed);
	sf::Vector2f getScreenPositionFromScreenX(float x);
	void generateWallAtWorldPositionY(float x);
};

#endif

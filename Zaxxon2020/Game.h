#pragma once
#ifndef GAME_H
#define GAME_H

#include "Bullet.h"

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
	static const sf::Vector2f startPos;
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
	sf::Vector2f viewVector;
	sf::Vector2f bulletVector;

	bool dead = false;
	

	sf::RenderWindow mWindow;
	sf::View view;

	std::vector<std::shared_ptr<Entity>> m_Entities;
	std::vector<std::shared_ptr<Bullet>> m_bullets;
	std::shared_ptr<Entity> player;
	std::shared_ptr<Entity> enemy;

	sf::Texture playerTexture;
	sf::Texture tWallTexture;
	sf::Texture enemyTexture;
	sf::Texture playerBulletTexture;
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

	void handleGameOver();

	void updatePlayer(sf::Time elapsedTime);
	void render(sf::Time elapsedTime);
	void renderSlider();
	void manageBullets(sf::Time elapsedTime);
	void manageCollisions();

	void processEvents();
	void handleInput(sf::Keyboard::Key key, bool pressed);
	sf::Vector2f getScreenPositionFromScreenX(float x);
	void generateWallAtWorldPositionY(float x);
};

#endif

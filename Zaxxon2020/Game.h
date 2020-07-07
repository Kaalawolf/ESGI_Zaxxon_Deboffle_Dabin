#pragma once
#ifndef GAME_H
#define GAME_H

#include "Entity.h"

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
	bool playerIsMovingUp;
	bool playerIsMovingLeft;
	bool playerIsMovingRight;
	bool playerIsMovingDown;
	sf::Vector2f viewVector;

	bool dead = false;
	

	sf::RenderWindow mWindow;
	sf::View view;

	std::vector<std::shared_ptr<Entity>> m_Entities;
	std::shared_ptr<Entity> player;

	sf::Texture playerTexture;
	sf::Texture bWallTexture;
	sf::Texture tWallTexture;
private:
	void initWindow();
	void initSprites();
	void initView();
	void initTextures();
	void resetGame();

	void resetPlayer();
	void initPlayer();

	void update(sf::Time elapsedTime);
	void render(sf::Time elapsedTime);
	void manageCollisions();

	void processEvents();
	void handleInput(sf::Keyboard::Key key, bool pressed);
	sf::Vector2f getScreenPositionFromScreenX(float x);
	void generateWallAtWorldPositionY(float x);
};

#endif

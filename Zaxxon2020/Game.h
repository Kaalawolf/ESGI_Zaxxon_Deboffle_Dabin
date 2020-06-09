#pragma once
#ifndef GAME_H
#define GAME_H

#include "pch.hpp"

const int mWindowsHeight = 600;
const int mWindowsWidth = 840;
const sf::String gameTitle = "Zaxxon 2020";

class Game
{
public:
	Game();

private:
	sf::RenderWindow mWindow;
	sf::CircleShape circle;
	sf::RectangleShape rect;
	int test = 2;
	sf::View view;

private:
	void initWindow();
	void refreshWindow();
};

#endif

#ifndef ENTITY_H
#define ENTITY_H

#include "pch.hpp"

enum EntityType
{
	player,
	weapon,
	enemyWeapon,
	enemyMasterWeapon,
	enemy,
	enemyMaster,
	block
};

class Entity
{
public:
	Entity();
	~Entity();
	sf::Sprite sprite;
	sf::Vector2u size;
	sf::Vector2f position;
};

#endif

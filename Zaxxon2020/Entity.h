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
	block,
	ui
};

class Entity
{
public:
	Entity();
	~Entity();
	void setWorldPosition(sf::Vector2f newWorldPosition);
	void setWorldZ(float z);
	sf::Vector2f getWorldPosition();
	float getWorldPositionZ();
	static sf::Vector2f worldToScreenPositions(sf::Vector2f positions);
	static sf::Vector2f screenToWorldPositions(sf::Vector2f positions);
	sf::Sprite sprite;
	sf::Vector2u size;
	EntityType type;

private:
	sf::Vector2f worldPosition;
	float worldPositionZ = 0;


};

#endif

#include "Entity.h"

Entity::Entity() {

}

Entity::~Entity() {

}

// Function to convert a world position to a screen (view) position
// ScreenX = 2*WorldX - 2*WorldY
// ScreenY = WorldX + WorldY
sf::Vector2f Entity::worldToScreenPositions(sf::Vector2f positions) {
	return sf::Vector2f(2 * positions.x - 2 * positions.y, positions.x + positions.y);
}

// Function to convert a screen (view) position to a world position
// WorldX = (ScreenX + 2*ScreenY)/4
// WorldY = (2*ScreenY - ScreenX)/4
sf::Vector2f Entity::screenToWorldPositions(sf::Vector2f positions) {
	return sf::Vector2f((positions.x + 2 * positions.y)/4, (2*positions.y - positions.x)/4);
}

void Entity::setWorldPosition(sf::Vector2f newPosition) {
	worldPosition = newPosition;
	sf::Vector2f screenpos = worldToScreenPositions(worldPosition);
	screenpos.y -= worldPositionZ;
	sprite.setPosition(screenpos);
}

void Entity::setWorldZ(float z)
{
	worldPositionZ = z;
	sf::Vector2f screenpos = worldToScreenPositions(worldPosition);
	screenpos.y -= worldPositionZ;
	sprite.setPosition(screenpos);
}

sf::Vector2f Entity::getWorldPosition() {
	return worldPosition;
}

float Entity::getWorldPositionZ(){
	return worldPositionZ;
}
#include "Bullet.h"

Bullet::Bullet() : Entity() {
	this->type = EntityType::weapon;
}

void Bullet::setSourceLocation(sf::Vector2f location, float zLocation) {
	sourceLocation = location;
	setWorldPosition(location);
	setWorldZ(zLocation);
}


Bullet::~Bullet() {

}
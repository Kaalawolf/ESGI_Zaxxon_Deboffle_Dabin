#include "EnemyBullet.h"
EnemyBullet::EnemyBullet() : Entity() {
	this->type = EntityType::enemyWeapon;
}

void EnemyBullet::setSourceLocation(sf::Vector2f location, float zLocation) {
	sourceLocation = location;
	setWorldPosition(location);
	setWorldZ(zLocation);
}


EnemyBullet::~EnemyBullet() {

}
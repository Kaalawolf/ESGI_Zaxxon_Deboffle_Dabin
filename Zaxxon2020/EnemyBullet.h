#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H
#include "Entity.h"
class EnemyBullet : public Entity
{

public:
    EnemyBullet();
    ~EnemyBullet();
    void setSourceLocation(sf::Vector2f location, float zLocation);
    sf::Vector2f getSourceLocation() { return sourceLocation; }

private:
    sf::Vector2f sourceLocation;
};

#endif

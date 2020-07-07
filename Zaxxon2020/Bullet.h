#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"

class Bullet : public Entity
{
public:
    void setSourceLocation(sf::Vector2f location, float zLocation);
    sf::Vector2f getSourceLocation() { return sourceLocation; }

private:
    sf::Vector2f sourceLocation;

public:
    Bullet();
    ~Bullet();
};

#endif
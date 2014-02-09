#pragma once
#include <SFML/System.hpp>
#include "Direction.h"
#include "World.h"

class Physics{
public:
    static Physics& getPhysics();
    void updatePlayer( sf::Vector2f input, Direction directionOfInput, 
            World& world );
    // Methods to update velocity when a collision is detected.
    void collideX();
    void collideY();
    void reset();
private:
    static Physics singleton;
    static const float GRAVITY_STRENGTH;
    static const float PLAYER_MASS;
    static const float HORIZONTAL_AIR_RESISTANCE;
    static const float VERTICAL_AIR_RESISTANCE;
    static const float MINIMUM_VELOCITY;
    static const float BOUNCE_FACTOR;
    static const float PLAYER_MAX_SPEED;
    static const float HULL_DAMAGE_THRESHOLD;
    static const float HULL_DAMAGE_SCALER;
    Physics(void);

    void damagePlayerHull( float velocity );

    float speed;
    sf::Vector2f velocity;
    sf::Vector2f previousLocation;
    sf::Vector2f acceleration;
};
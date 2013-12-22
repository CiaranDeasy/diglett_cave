#pragma once
#include <SFML/System.hpp>

class Physics{
public:
    static Physics& getPhysics();
    void updatePlayer(sf::Vector2f force);
    // Methods to update velocity when a collision is detected.
    void collideX();
    void collideY();
    void reset();
private:
    static Physics singleton;
    Physics(void);
    float speed;
    sf::Vector2f velocity;
    sf::Vector2f previousLocation;
    sf::Vector2f acceleration;
};
#pragma once
#include <SFML/System.hpp>

class Physics{
public:
    static Physics& getPhysics();
    void updatePlayer(sf::Vector2f force);
private:
    static Physics singleton;
    Physics(void);
    float speed;
    sf::Vector2f velocity;
    sf::Vector2f previousLocation;
    sf::Vector2f acceleration;
};
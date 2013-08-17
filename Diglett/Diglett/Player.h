#pragma once
#include <SFML/System.hpp>
class Player {
public:
    sf::Vector2f getPosition();
    void move( float x, float y );
    Player(void);
    ~Player(void);
private:
    sf::Vector2f position;
};


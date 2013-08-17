#pragma once
#include <SFML/System.hpp>
class Player {
public:
    sf::Vector2f getPosition();
    Player(void);
    ~Player(void);
private:
    sf::Vector2f position;
};


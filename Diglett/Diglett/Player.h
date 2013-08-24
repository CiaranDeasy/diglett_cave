#pragma once
#include <SFML/System.hpp>
class Player {
public:
    static Player& getPlayer();
    sf::Vector2f getPosition();
    void move( float x, float y );
    ~Player(void);
private:
    static Player singleton;
    sf::Vector2f position;
    Player(void);
};
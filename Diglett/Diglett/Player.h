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
    // The player's position is their centre. Adding a "Clip" to the 
    // appropriate component of the position gives a line of the player's 
    // bounding box.
    sf::Vector2f position;
    float topClip;
    float bottomClip;
    float leftClip;
    float rightClip;
    Player(void);
};
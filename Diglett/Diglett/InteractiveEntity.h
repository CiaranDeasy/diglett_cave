#pragma once
#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "Player.h"

class InteractiveEntity : public sf::Drawable {

public:
    InteractiveEntity();
    ~InteractiveEntity();
    sf::Vector2f getPosition();
    sf::Sprite *getSprite();
    
    // This function is called when the player interacts with the entity.
    virtual void interact( 
            GameWindow *gameWindow, Player& player ) = 0;

protected:
    // Position of the entity in the game world.
    sf::Vector2f position;

    // Sprite representing the entity in the game world.
    sf::Sprite *sprite;

};


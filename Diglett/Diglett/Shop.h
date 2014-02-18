#pragma once
#include "InteractiveEntity.h"
#include "GameWindow.h"

/* Represents the shop as a drawable, interactive entity in the game world. */

class Shop : public InteractiveEntity {

public:
    Shop();
    ~Shop();
    virtual void interact( 
            GameWindow *gameWindow, sf::Font& font, Player& player );
    virtual void draw( 
            sf::RenderTarget& target, sf::RenderStates states ) const;

private:
    static const sf::Vector2f POSITION;
    static const std::string SPRITE_FILE;
    sf::Texture *texture;

};

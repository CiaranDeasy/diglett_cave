#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "InteractiveEntity.h"

/* An instance of this class represents the game world. */

class World : public sf::Drawable {
public:

    World( Player& player );
    ~World();

    // Draws the GUI to the given RenderTarget using the options specified 
    // in the given RenderStates.
    virtual void draw( 
            sf::RenderTarget& target, sf::RenderStates states ) const;

    void interact( GameWindow *gamewindow, sf::Font& font );

private: 
    Player& player;
    std::vector<InteractiveEntity *> interactiveEntities;
};

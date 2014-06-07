#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "InteractiveEntity.h"
#include "WorldData.h"

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
    
    const Tile& getTile( int x, int y ) const;
    const Tile& getTile( sf::Vector2i in ) const;
    
    // Digs the tile at the given co-ordinates and adds an item to the player's
    // inventory if appropriate.
    void digTile( sf::Vector2i tileCoords, Player& player );

	// Returns the position vector of the shop.
	const sf::Vector2f& getShopPosition();

private: 
	static enum InteractiveEntities {
		keShop = 0
	};

    Player& player;
    WorldData worldData;
    std::vector<InteractiveEntity *> interactiveEntities;
};

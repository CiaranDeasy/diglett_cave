#include "Tile.h"
#include "GameWindow.h"
#include "Constants.h"
#include "Player.h"

Tile::Tile(void) {
    this->type = 0; //Air
}

Tile::Tile(int type) {
    this->type = type;
}

Tile::~Tile(void) {
}

void Tile::dig() {
    Item *item = this->lookupType( type ).createItem();
    if( item->getName() != "NULL" ) {
        // Add the item to the player's inventory.
        Player::getPlayer().getInventory().addItem( item );
    }
    // Change this block to air.
    type = 0; //Air
}

bool Tile::isDiggable() {
   return lookupType( this->type ).isDiggable();
}

bool Tile::isSolid() {
   return lookupType( this->type ).isSolid();
}

bool Tile::isOre() {
    return ( this->type != 0 && this->type != 1 && this->type != 2 );
}

sf::Sprite *Tile::getSprite() {
    return lookupType( this->type ).getSprite();
}

void Tile::initialiseTypes() {
    types.push_back( TileType( "Air", 
            GameWindow::makeSquareSprite( 
                sf::Color( 156, 94, 0, 255 ), PIXELS_PER_TILE ), 
            false, false, 0 ) );
    types.push_back( TileType( "Surface", 
            GameWindow::makeSquareSprite( 
                sf::Color::Blue, PIXELS_PER_TILE ), 
            false, false, 0 ) );
    types.push_back( TileType( "Dirt", 
            GameWindow::makeSquareSprite( 
                sf::Color( 126, 64, 0, 255 ), PIXELS_PER_TILE ), 
            true, true, 0 ) );
    types.push_back( TileType( "Gold", 
            GameWindow::makeSquareSprite( 
                sf::Color( 255, 215, 0, 255 ), PIXELS_PER_TILE ), 
            true, true, 1 ) );
}

TileType& Tile::lookupType( int id ) {
    return types[id];
}

std::vector<TileType> Tile::types = std::vector<TileType>();
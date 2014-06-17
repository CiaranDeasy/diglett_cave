#include "Tile.h"
#include "GameWindow.h"
#include "Constants.h"
#include "Player.h"
#include "Resources.h"

Tile::Tile(void) {
    this->type = 0; //Air
}

Tile::Tile(int type) {
    this->type = type;
}

Tile::~Tile(void) {
}

void Tile::dig( Player& player ) {
    Item *item = this->lookupType( type ).createItem();
    if( item->getName() != "NULL" ) {
        // Add the item to the player's inventory.
        player.getInventory().addItem( item );
    }
    // Change this block to air.
    type = 0; //Air
}

bool Tile::isDiggable() const {
   return lookupType( this->type ).isDiggable();
}

bool Tile::isSolid() const {
   return lookupType( this->type ).isSolid();
}

bool Tile::isOre() const {
    return ( this->type != 0 && this->type != 1 && this->type != 2 );
}

sf::Sprite *Tile::getSprite() {
    return lookupType( this->type ).getSprite();
}

void Tile::initialiseTypes() {
    types.push_back( TileType( "Air", 
            new sf::Sprite( Resources::getResources().getAirTileTexture() ), 
            false, false, 0 ) );
    types.push_back( TileType( "Surface", 
            new sf::Sprite(Resources::getResources().getSurfaceTileTexture()),
            false, false, 0 ) );
    types.push_back( TileType( "Dirt", 
            new sf::Sprite( Resources::getResources().getDirtTileTexture() ),
            true, true, 0 ) );
    types.push_back( TileType( "Gold", 
            new sf::Sprite( Resources::getResources().getGoldTileTexture() ),
            true, true, 1 ) );
}

TileType& Tile::lookupType( int id ) {
    return types[id];
}

std::vector<TileType> Tile::types = std::vector<TileType>();
#include "Tile.h"
#include "GameWindow.h"

Tile::Tile(void) {
    this->type = 0; //Air
}

Tile::Tile(int type) {
    this->type = type;
}

Tile::~Tile(void) {
}

void Tile::dig() { type = 0; } //Air

bool Tile::isDiggable() {
   return lookupType( this->type ).isDiggable();
}

bool Tile::isSolid() {
   return lookupType( this->type ).isSolid();
}

sf::Sprite *Tile::getSprite() {
    return lookupType( this->type ).getSprite();
}

void Tile::initialiseTypes() {
    types.push_back( TileType( "Air", 
            GameWindow::makeSquareSprite( 
                sf::Color( 156, 94, 0, 255 ) ), 
            false, false ) );
    types.push_back( TileType( "Surface", 
            GameWindow::makeSquareSprite( 
                sf::Color::Blue ), 
            false, false ) );
    types.push_back( TileType( "Dirt", 
            GameWindow::makeSquareSprite( 
                sf::Color( 126, 64, 0, 255 ) ), 
            true, true ) );
    types.push_back( TileType( "Gold", 
            GameWindow::makeSquareSprite( 
                sf::Color( 255, 215, 0, 255 ) ), 
            true, true ) );
}

TileType& Tile::lookupType( int id ) {
    return types[id];
}

std::vector<TileType> Tile::types = std::vector<TileType>();
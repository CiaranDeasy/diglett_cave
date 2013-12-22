#include "Tile.h"
#include "GameWindow.h"

TileType& Tile::lookupType( int id ) {
    return types[id];
}

Tile::Tile(void) {
    this->type = 0; //Air
}

Tile::Tile(int type) {
    this->type = type;
}

Tile::~Tile(void) {
}

int Tile::getType() { return type; }

void Tile::dig() { type = 0; } //Air

bool Tile::isDiggable() {
   return lookupType( this->type ).isDiggable();
}

void Tile::initialiseTypes() {
    types.push_back( TileType( "Air", 
            GameWindow::makeSquareSprite( 
                sf::Color( 156, 94, 0, 255 ) ), 
            false ) );
    types.push_back( TileType( "Surface", 
            GameWindow::makeSquareSprite( 
                sf::Color::Blue ), 
            false ) );
    types.push_back( TileType( "Dirt", 
            GameWindow::makeSquareSprite( 
                sf::Color( 126, 64, 0, 255 ) ), 
            true ) );
    types.push_back( TileType( "Gold", 
            GameWindow::makeSquareSprite( 
                sf::Color( 255, 215, 0, 255 ) ), 
            true ) );
}

std::vector<TileType> Tile::types = std::vector<TileType>();
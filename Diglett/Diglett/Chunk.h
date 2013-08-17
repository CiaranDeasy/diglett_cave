#pragma once
#include "Tile.h"
#include <SFML/System.hpp>
const int CHUNK_SIDE = 20;

class Chunk {
public:
    sf::Vector2i getPosition();
    Tile getTile( int x, int y );

    // Constructor which takes a type of tile and makes a chunk consisting 
    // entirely of tiles of that type.
    Chunk( sf::Vector2i, Tile::Type );
    ~Chunk( void );

    // Default constructor not supported.
    // Present to keep arrays happy.
    Chunk( void );
private:
    // Tiles in the chunk.
    Tile tiles[CHUNK_SIDE][CHUNK_SIDE];

    // Tile index of tiles[0][0]
    sf::Vector2i position;
};


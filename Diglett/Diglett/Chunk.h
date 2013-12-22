#pragma once
#include "Tile.h"
#include <SFML/System.hpp>
#include "Constants.h"

class Chunk {
public:
    sf::Vector2i getPosition();
    // Takes index relative to the chunk's own array.
    Tile& getRelativeTile( int x, int y );
    // Takes index of tile in absolute world co-ordinates.
    Tile& getAbsoluteTile( int x, int y );

    // Constructor which takes a type of tile and makes a chunk consisting 
    // entirely of tiles of that type.
    Chunk( sf::Vector2i pos, int type );
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


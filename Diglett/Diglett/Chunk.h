#pragma once
#include "Tile.h"
#include <SFML/System.hpp>
#include "Constants.h"
#include <array>
#include "Player.h"

class Chunk {
public:
    // Constructor which takes a type of tile and makes a chunk consisting 
    // entirely of tiles of that type.
    Chunk( sf::Vector2i pos, int type );
    ~Chunk( void );

    sf::Vector2i getPosition();
    // Takes index relative to the chunk's own array.
    const Tile& getRelativeTile( int x, int y ) const;
    // Takes index of tile in absolute world co-ordinates.
    const Tile& getAbsoluteTile( int x, int y ) const;

    // Digs the tile at the given co-ordinates and adds an item to the player's
    // inventory if appropriate.
    void digAbsoluteTile( int x, int y, Player& player );

    // Default constructor not supported.
    // Present to keep arrays happy.
    Chunk( void );
private:
    // Tiles in the chunk.
    std::array<std::array<Tile, CHUNK_SIDE>, CHUNK_SIDE> tiles;

    // Tile index of tiles[0][0]
    sf::Vector2i position;

    Tile randomTileType( int depth );

    int scaledDepth( int depth );
};


#pragma once
#ifndef TILE_H
#define TILE_H

#include "TileType.h"
#include <vector>
#include "Player.h"

class Tile {

public:

    // Initialises types vector. Cannot be done at static initialisation due to a 
    // limitation in the SFML library. Must be called afterwards.
    static void initialiseTypes();

    // Takes a numerical ID of a tile type and returns the appropriate TileType
    // object.
    Tile(void);
    Tile(int type);
    ~Tile(void);

    // Changes the tile to air, and adds an item to the player's inventory.
    void dig( Player& player );

    bool isDiggable() const;
    bool isSolid() const;
    bool isOre() const;
    sf::Sprite *getSprite();

private:
    static TileType& lookupType( int id );
    static std::vector<TileType> types;
    int type;
};

#endif // TILE_H

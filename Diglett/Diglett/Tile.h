#pragma once
#include "TileType.h"
#include <vector>

class Tile {

public:

    // Initialises types vector. Cannot be done at static initialisation due to a 
    // limitation in the SFML library. Must be called afterwards.
    static void initialiseTypes();

    // Takes a numerical ID of a tile type and returns the appropriate TileType
    // object.
    static TileType& lookupType( int id );
    Tile(void);
    Tile(int type);
    ~Tile(void);
    int getType();
    void dig();
    bool isDiggable();
    bool isSolid();

private:
    static std::vector<TileType> types;
    int type;
};
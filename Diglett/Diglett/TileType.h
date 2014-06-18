#pragma once
#ifndef TILE_TYPE_H
#define TILE_TYPE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Item.h"

class TileType {

public:
    TileType(void);
    TileType( std::string name, sf::Sprite *sprite, bool diggable, bool solid,
            int item );
    ~TileType(void);
    sf::Sprite *getSprite();
    bool isDiggable();
    bool isSolid();
    Item *createItem();

private:
    std::string name;
    sf::Sprite *sprite;
    bool diggable;
    bool solid;

    // An integer ID representing the type of item that this type of tile
    // drops.
    int item;

};

#endif // TILE_TYPE_H

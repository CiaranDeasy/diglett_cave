#pragma once
#ifndef ITEM_H
#define ITEM_H

#include "ItemType.h"
#include <vector>
#include <string>

class Item {

public:

    // Initialises types vector. Cannot be done at static initialisation due to a 
    // limitation in the SFML library. Must be called afterwards.
    static void initialiseTypes();

    Item( int type );
    ~Item(void);
    std::string getName();
    sf::Sprite *getSprite();
    int getValue();

private:
    
    static std::vector<ItemType> types;

    // Takes a numerical ID of a tile type and returns the appropriate ItemType
    // object.
    static ItemType& lookupType( int id );

    int type;

};

#endif // ITEM_H

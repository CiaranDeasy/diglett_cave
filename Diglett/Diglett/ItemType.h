#pragma once
#ifndef ITEM_TYPE_H
#define ITEM_TYPE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class ItemType
{
public:
    ItemType( std::string name, sf::Sprite *sprite, int value );
    ~ItemType(void);
    std::string getName();
    sf::Sprite *getSprite();
    int getValue();

private:
    std::string name;
    sf::Sprite *sprite;
    int value;

};

#endif // ITEM_TYPE_H

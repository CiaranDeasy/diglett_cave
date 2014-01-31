#pragma once
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


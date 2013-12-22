#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class ItemType
{
public:
    ItemType(void);
    ItemType( std::string name, sf::Sprite *sprite );
    ~ItemType(void);
    std::string getName();
    sf::Sprite *getSprite();

private:
    std::string name;
    sf::Sprite *sprite;

};


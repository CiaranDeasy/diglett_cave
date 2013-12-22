#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class TileType {

public:
    TileType(void);
    TileType(std::string name, sf::Sprite *sprite, bool diggable, bool solid);
    ~TileType(void);
    sf::Sprite *getSprite();
    bool isDiggable();
    bool isSolid();

private:
    std::string name;
    sf::Sprite *sprite;
    bool diggable;
    bool solid;

};


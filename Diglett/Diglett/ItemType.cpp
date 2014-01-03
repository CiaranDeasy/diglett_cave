#include "ItemType.h"

ItemType::ItemType( std::string name, sf::Sprite *sprite ) {
    this->name = name;
    this->sprite = sprite;
}

ItemType::~ItemType(void) {}

std::string ItemType::getName() { return name; }

sf::Sprite *ItemType::getSprite() { return sprite; }
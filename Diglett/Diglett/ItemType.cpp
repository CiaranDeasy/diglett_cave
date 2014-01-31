#include "ItemType.h"

ItemType::ItemType( std::string name, sf::Sprite *sprite, int value ) {
    this->name = name;
    this->sprite = sprite;
    this->value = value;
}

ItemType::~ItemType(void) {}

std::string ItemType::getName() { return name; }

sf::Sprite *ItemType::getSprite() { return sprite; }

int ItemType::getValue() { return value; }

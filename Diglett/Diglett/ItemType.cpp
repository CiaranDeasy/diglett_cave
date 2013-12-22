#include "ItemType.h"

ItemType::ItemType(void) {}

ItemType::~ItemType(void) {}

std::string ItemType::getName() { return name; }

sf::Sprite *ItemType::getSprite() { return sprite; }
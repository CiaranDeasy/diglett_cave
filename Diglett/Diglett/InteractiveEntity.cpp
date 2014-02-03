#include "InteractiveEntity.h"

InteractiveEntity::InteractiveEntity() {}

InteractiveEntity::~InteractiveEntity() {}

sf::Vector2f InteractiveEntity::getPosition() { return position; }

sf::Sprite *InteractiveEntity::getSprite() { return sprite; }

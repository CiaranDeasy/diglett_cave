#include "TileType.h"
#include "Constants.h"

TileType::TileType(void) {
    // Not a valid constructor.
}

TileType::TileType( std::string name, sf::Sprite *sprite, bool diggable, 
                   bool solid ) {
     this->name = name;
     this->sprite = sprite;
     sprite->setOrigin( 0, PIXELS_PER_TILE );
     this->diggable = diggable;
     this->solid = solid;
}


TileType::~TileType(void) {
}

sf::Sprite *TileType::getSprite() { return sprite; }

bool TileType::isDiggable() { return diggable; }

bool TileType::isSolid() { return solid; }
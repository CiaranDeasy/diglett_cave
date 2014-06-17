#include "Item.h"
#include "GameWindow.h"
#include "Constants.h"
#include "Resources.h"

void Item::initialiseTypes() {
    types.push_back( ItemType( "NULL", NULL, 0 ) ); // Indicates no item.
    types.push_back( ItemType( "Gold", 
		    new sf::Sprite( Resources::getResources().getGoldItemTexture() ),
            100 ) );
}

Item::Item( int type ) {
    this->type = type;
}

Item::~Item(void) {}

std::string Item::getName() {
    return lookupType( this->type ).getName();
}

sf::Sprite *Item::getSprite() {
    return lookupType( this->type ).getSprite();
}

int Item::getValue() {
    return lookupType( this->type ).getValue();
}

ItemType& Item::lookupType( int id ) {
    return types[id];
}

std::vector<ItemType> Item::types = std::vector<ItemType>();
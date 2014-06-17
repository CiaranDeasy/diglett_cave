#include "Shop.h"
#include "ShopGameState.h"
#include "Utility.h"
#include "Resources.h"

Shop::Shop() {
    this->position = POSITION;
    sprite = new sf::Sprite();
    this->sprite->setTexture( Resources::getResources().getShopTexture() );
    sf::FloatRect bounds = sprite->getLocalBounds();
    sprite->setOrigin( bounds.left + bounds.width / 2, 
            bounds.top + bounds.height / 2 );
    sprite->setPosition( Utility::coordsGameToWindow( position ) );
}

Shop::~Shop() {
    delete sprite;
}

void Shop::interact( GameWindow *gameWindow, Player& player ) {
    gameWindow->pushNewState( new ShopGameState( gameWindow, player ) );
}

void Shop::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( *sprite, states );
}

const sf::Vector2f Shop::POSITION = sf::Vector2f( 5, 1 );

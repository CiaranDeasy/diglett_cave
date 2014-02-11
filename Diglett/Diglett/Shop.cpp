#include "Shop.h"
#include "ShopGameState.h"
#include "Utility.h"

Shop::Shop() {
    this->position = POSITION;
    this->sprite = GameWindow::makeCircleSprite( sf::Color::Black );
    sprite->setPosition( Utility::coordsGameToWindow( position ) );
}

Shop::~Shop() {
    delete sprite;
}

void Shop::interact( GameWindow *gameWindow, sf::Font& font, Player& player ) {
    gameWindow->pushNewState( new ShopGameState( gameWindow, font, player ) );
}

void Shop::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( *sprite );
}

const sf::Vector2f Shop::POSITION = sf::Vector2f( 5, 1 );

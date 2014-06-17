#include "Shop.h"
#include "ShopGameState.h"
#include "Utility.h"

Shop::Shop() {
    this->position = POSITION;
    texture = new sf::Texture();
    if ( !texture->loadFromFile( SPRITE_FILE ) ) {
        std::cerr << "Failed to load file: " << SPRITE_FILE << "\n";
        exit(1);
    }
    sprite = new sf::Sprite();
    this->sprite->setTexture( *texture );
    sf::FloatRect bounds = sprite->getLocalBounds();
    sprite->setOrigin( bounds.left + bounds.width / 2, 
            bounds.top + bounds.height / 2 );
    sprite->setPosition( Utility::coordsGameToWindow( position ) );
}

Shop::~Shop() {
    delete sprite;
    delete texture;
}

void Shop::interact( GameWindow *gameWindow, Player& player ) {
    gameWindow->pushNewState( new ShopGameState( gameWindow, player ) );
}

void Shop::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( *sprite );
}

const sf::Vector2f Shop::POSITION = sf::Vector2f( 5, 1 );

const std::string Shop::SPRITE_FILE = "Sprites/shop.png";

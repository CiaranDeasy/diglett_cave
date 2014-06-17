#include "NewItemVisual.h"
#include "Constants.h"
#include "Resources.h"

NewItemVisual::NewItemVisual( Item *item ) {
    ticksRemaining = TICKS_TO_LIVE;
    stepSize = sf::Vector2f( 
            ( (float) FINAL_DISPLACEMENT.x ) / TICKS_TO_LIVE, 
            ( (float) FINAL_DISPLACEMENT.y ) / TICKS_TO_LIVE );

    // Make the text object, to determine the size of the sprite renderer.
    sf::Text text = sf::Text( 
		    item->getName(), Resources::getResources().getFont(), TEXT_SIZE );

    sf::RenderTexture renderer;
    renderer.create( text.getLocalBounds().width + 2, 
            TEXT_SIZE + 2 + SPRITE_SEPARATION + PIXELS_PER_ITEM_SPRITE );
    renderer.clear(sf::Color::Transparent);
    // Draw the sprite.
    item->getSprite()->setPosition( 
            ( renderer.getSize().x / 2 ) - ( PIXELS_PER_ITEM_SPRITE / 2 ), 0 );
    renderer.draw( *item->getSprite() );
    // Draw the background.
    sf::RectangleShape textBackground = sf::RectangleShape( 
            sf::Vector2f( renderer.getSize().x, renderer.getSize().y ) );
    textBackground.setFillColor( BACKGROUND_COLOR );
    textBackground.setPosition( 
            0, PIXELS_PER_ITEM_SPRITE + SPRITE_SEPARATION );
    renderer.draw( textBackground );
    // Draw the text.
    text.setColor( TEXT_COLOR );
    text.setPosition( 1, PIXELS_PER_ITEM_SPRITE + SPRITE_SEPARATION );
    renderer.draw( text );
    // Make the full sprite.
    renderer.display();
    sf::Texture texture = renderer.getTexture();
    texturePointer = new sf::Texture( texture );
    sprite = new sf::Sprite( *texturePointer );
    sprite->setOrigin( renderer.getSize().x / 2, renderer.getSize().y / 2 );
}

NewItemVisual::~NewItemVisual(void) {
    delete texturePointer;
    delete sprite;
}

void NewItemVisual::draw( 
        sf::RenderTarget& target, 
        sf::RenderStates states ) const {
    // Draw the sprite.
    int stepsSoFar = TICKS_TO_LIVE - ticksRemaining;
    sprite->setPosition( target.getSize().x /2 + ( stepSize.x * stepsSoFar ), 
            target.getSize().y /2 + ( stepSize.y * stepsSoFar ) );
    target.draw( *sprite );
}

bool NewItemVisual::isAlive() { return ticksRemaining != 0; }

void NewItemVisual::tick() { 
    if( ticksRemaining > 0 ) {
        ticksRemaining--;
        sprite->move( stepSize );
    }
}

const int NewItemVisual::TICKS_TO_LIVE = 60;
const sf::Vector2i NewItemVisual::FINAL_DISPLACEMENT = sf::Vector2i( 0, -50 );
const int NewItemVisual::TEXT_SIZE = 12;
const sf::Color NewItemVisual::BACKGROUND_COLOR = 
        sf::Color( 0, 0, 0, 128 );
const sf::Color NewItemVisual::TEXT_COLOR = 
        sf::Color( 255, 255, 255, 255 );
const int NewItemVisual::SPRITE_SEPARATION = 6;
#include "NewItemVisual.h"
#include "Constants.h"

NewItemVisual::NewItemVisual( sf::Font& font, Item *item ) : font(font) {
    ticksRemaining = TICKS_TO_LIVE;
    stepSize = sf::Vector2f( 
            ( FINAL_POSITION.x - INITIAL_POSITION.x ) / TICKS_TO_LIVE, 
            ( FINAL_POSITION.y - INITIAL_POSITION.y ) / TICKS_TO_LIVE );

    // Make the text object, to determine the size of the sprite renderer.
    sf::Text text = sf::Text( item->getName(), font, TEXT_SIZE );

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
    sprite->setPosition( INITIAL_POSITION );
}

NewItemVisual::~NewItemVisual(void) {
    delete texturePointer;
    delete sprite;
}

void NewItemVisual::draw( 
        sf::RenderTarget& target, 
        sf::RenderStates states ) const {
    // Move the sprite.
    sprite->move( stepSize );
    // Draw the sprite.
    target.draw( *sprite );
}

bool NewItemVisual::isAlive() { return ticksRemaining != 0; }

void NewItemVisual::tick() { ticksRemaining--; }

const int NewItemVisual::TICKS_TO_LIVE = 60;
const sf::Vector2f NewItemVisual::INITIAL_POSITION = 
        sf::Vector2f( WINDOW_RESOLUTION.x /2, WINDOW_RESOLUTION.y /2 );
const sf::Vector2f NewItemVisual::FINAL_POSITION = 
        INITIAL_POSITION + sf::Vector2f( 0, -50 );
const int NewItemVisual::TEXT_SIZE = 12;
const sf::Color NewItemVisual::BACKGROUND_COLOR = 
        sf::Color( 0, 0, 0, 128 );
const sf::Color NewItemVisual::TEXT_COLOR = 
        sf::Color( 255, 255, 255, 255 );
const int NewItemVisual::SPRITE_SEPARATION = 6;
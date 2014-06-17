#include "TextPopUp.h"
#include <iostream>

TextPopUp::TextPopUp( std::string message, const sf::Font& font ) : font(font) {
    this->message = message;
}

TextPopUp::~TextPopUp(void) {
}

void TextPopUp::draw( 
        sf::RenderTarget& target, 
        sf::RenderStates states ) const {
    // Determine the position vector.
    sf::Vector2i position = sf::Vector2i( 
            target.getSize().x / 2, target.getSize().y / 4 );
    // Make the text.
    sf::Text text = sf::Text( message, font, TEXT_SIZE );
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin( bounds.left + bounds.width / 2, 
            bounds.top + bounds.height / 2 );
    text.setPosition( position.x, position.y );
    // Draw the background.
    sf::RectangleShape background = sf::RectangleShape( sf::Vector2f( 
            bounds.width + 2*BORDER_SIZE, bounds.height + 2*BORDER_SIZE ) );
    background.setOrigin( 
            background.getSize().x /2, background.getSize().y /2 );
    background.setFillColor( BACKGROUND_COLOR );
    background.setPosition( position.x, position.y );
    target.draw( background );
    // Draw the text.
    target.draw( text );
}

const int TextPopUp::BORDER_SIZE = 10;
const int TextPopUp::TEXT_SIZE = 18;
const sf::Color TextPopUp::BACKGROUND_COLOR = sf::Color( 0, 0, 0, 255 );
const sf::Color TextPopUp::TEXT_COLOR = 
        sf::Color( 255, 255, 255, 255 );

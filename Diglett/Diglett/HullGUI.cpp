#include "HullGUI.h"

HullGUI::HullGUI( sf::Font& font ) : font(font) {
}

HullGUI::~HullGUI(void) {
}

void HullGUI::draw( 
        sf::RenderTarget& target, 
        sf::RenderStates states ) const {
    // Set up the view.
    // TODO: make the view dependent on the states input.
    sf::View view = sf::View( sf::Vector2f( 0.0f, 0.0f ), 
            sf::Vector2f( target.getSize().x, target.getSize().y ) );
    view.setViewport( sf::FloatRect( 0.0f, 0.0f, 1.0f, 1.0f ) );
    view.zoom( 1.0 );
    target.setView( view );
    // Draw the background.
    sf::RectangleShape background = sf::RectangleShape( 
            sf::Vector2f( GUI_SIZE.x, GUI_SIZE.y ) );
    background.setFillColor( BACKGROUND_COLOR );
    background.setPosition( 
            POSITION.x, POSITION.y );
    target.draw( background );
    // Fill according to current hull strength.
    float currentHullFraction = Player::getPlayer().getCurrentHull() / 
            Player::getPlayer().getMaxHull();
    sf::RectangleShape fill = sf::RectangleShape( 
            sf::Vector2f( 
                currentHullFraction * ( GUI_SIZE.x - 2*BORDER_THICKNESS ), 
                ( GUI_SIZE.y - 2*BORDER_THICKNESS ) ) );
    fill.setFillColor( FILL_COLOR );
    fill.setPosition( POSITION.x + BORDER_THICKNESS, 
            POSITION.y + BORDER_THICKNESS );
    target.draw( fill );
    // Draw the text.
    std::string textString = 
            std::to_string( Player::getPlayer().getCurrentHull() ) + "/" + 
            std::to_string( Player::getPlayer().getMaxHull() );
    sf::Text text = sf::Text( textString, font, TEXT_SIZE );
    text.setStyle( sf::Text::Bold );
    text.setOrigin( text.getLocalBounds().width / 2, 
            text.getLocalBounds().height / 2 );
    text.setPosition( POSITION.x + (GUI_SIZE.x/2), 
            POSITION.y + (GUI_SIZE.y/2) );
    target.draw( text );
}

const sf::Vector2i HullGUI::POSITION = sf::Vector2i( 290, -290 );
const sf::Vector2i HullGUI::GUI_SIZE = sf::Vector2i( 100, 20 );
const int HullGUI::TEXT_SIZE = 12;
const sf::Color HullGUI::BACKGROUND_COLOR = sf::Color( 0, 0, 0, 255 );
const sf::Color HullGUI::FILL_COLOR = sf::Color( 255, 0, 0, 255 );
const sf::Color HullGUI::TEXT_COLOR = 
        sf::Color( 255, 255, 255, 255 );
const int HullGUI::BORDER_THICKNESS = 2;
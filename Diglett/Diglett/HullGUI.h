#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

/* An instance of this class represents an interface element displaying the 
   player's current hull strength.
*/

class HullGUI : public sf::Drawable {
public:

    HullGUI( sf::Font& font );
    ~HullGUI();

    // Draws the GUI to the given RenderTarget using the options specified 
    // in the given RenderStates.
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

private: 
    
    static const sf::Vector2i POSITION;
    static const sf::Vector2i GUI_SIZE;
    static const int TEXT_SIZE;
    static const sf::Color BACKGROUND_COLOR;
    static const sf::Color FILL_COLOR;
    static const sf::Color TEXT_COLOR;
    static const int BORDER_THICKNESS;

    sf::Font& font;

};


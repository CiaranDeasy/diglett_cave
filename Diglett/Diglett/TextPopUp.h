#pragma once
#include <SFML/Graphics.hpp>

/* An instance of this class represents an interface element displaying the 
   player's current hull strength.
*/

class TextPopUp : public sf::Drawable {
public:

    TextPopUp( std::string message, const sf::Font& font );
    ~TextPopUp();

    // Draws the pop-up to the given RenderTarget.
    virtual void draw( 
            sf::RenderTarget& target, sf::RenderStates states ) const;

private: 
    
    // The number of pixels between the text and the edges of the pop-up.
    static const int BORDER_SIZE;

    // The position of the game window is the centre of the top half of the 
    // window.

    static const int TEXT_SIZE;
    static const sf::Color BACKGROUND_COLOR;
    static const sf::Color TEXT_COLOR;

    const sf::Font& font;
    std::string message;

};


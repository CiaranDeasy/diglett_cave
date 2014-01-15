#pragma once
#include <SFML/Graphics.hpp>

/* An instance of this class represents an interface element displaying the 
   player's current hull strength.
*/

class DebugOverlayGUI : public sf::Drawable {
public:

    DebugOverlayGUI( sf::Font& font );
    ~DebugOverlayGUI();

    // Shows or hides the GUI.
    void toggle();

    // Returns true if the GUI is visible in the game window.
    bool isVisible() const;

    // Draws the GUI to the given RenderTarget.
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

private: 
    
    // The position of the GUI in the game window. Positive values indicate 
    // offset from the top/left, negative from the bottom/right.
    static const sf::Vector2i POSITION;
    static const sf::Vector2i GUI_SIZE;
    static const int TEXT_SIZE;
    static const sf::Color BACKGROUND_COLOR;
    static const sf::Color TEXT_COLOR;

    // Indicates whether the GUI is visible in the game window.
    bool visible;

    // Font object for the GUI text.
    sf::Font& font;

};


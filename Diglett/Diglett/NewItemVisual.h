#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"

/* When an item is acquired in-game, a corresponding visual is displayed. This
   visual is represented by an instance of the NewItemVisual class.
*/

class NewItemVisual : public sf::Drawable {
public:

    NewItemVisual( sf::Font& font, Item *item );
    ~NewItemVisual();

    // Draws the visual to the given RenderTarget using the options specified 
    // in the given RenderStates.
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

    // Returns true if the visual should be displayed.
    bool isAlive();

    // Decrements the remaining ticks to live by one.
    void tick();

private: 
    
    static const int TICKS_TO_LIVE;
    static const sf::Vector2f INITIAL_POSITION;
    static const sf::Vector2f FINAL_POSITION;
    static const int TEXT_SIZE;
    static const sf::Color BACKGROUND_COLOR;
    static const sf::Color TEXT_COLOR;

    // Number of pixels separating the item sprite and its name.
    static const int SPRITE_SEPARATION;

    sf::Font& font;
    //sf::Vector2f currentPosition;
    sf::Sprite *sprite;

    // Texture pointer for cleanup.
    sf::Texture *texturePointer;

    // Vector representing the movement of the visual on each tick.
    sf::Vector2f stepSize;

    // Ticks to go before the visual disappears.
    int ticksRemaining;

};


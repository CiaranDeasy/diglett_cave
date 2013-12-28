#pragma once
#include <SFML/Graphics.hpp>

class InventoryGUI : public sf::Drawable {
public:

    InventoryGUI( sf::Font& font );
    ~InventoryGUI(void);
    
    // Toggles whether the inventory is visible in the game window.
    void toggle();

    // Draws the inventory GUI to the given RenderTarget using the options
    // specified in the given RenderStates.
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    
    // Returns true if the inventory should be visible in the game window.
    bool isVisible();

private: 
    
    static const int DEFAULT_BORDER;
    static const int DEFAULT_ITEMS_PER_COL;
    static const sf::Vector2i DEFAULT_ENTRY_SIZE;
    static const int DEFAULT_SPRITE_SEPARATION;
    static const int DEFAULT_TEXT_SIZE;
    static const sf::Color DEFAULT_BACKGROUND_COLOR;
    static const sf::Color DEFAULT_TEXT_COLOR;

    // Number of pixels between edges of inventory GUI and its contents.
    int border;

    // Number of items that should be displayed vertically in the inventory 
    // GUI.
    int itemsPerCol;

    // Size in pixels of a single entry in the inventory.
    sf::Vector2i entrySize;

    // Number of pixels separating an item sprite and its name.
    int spriteSeparation;

    int textSize;
    sf::Color backgroundColor;
    sf::Color textColor;
    sf::Font font;

    bool visible;
    int expectedInventorySize;
    
    // Creates a rectangular background for the GUI.
    sf::RectangleShape *makeInventoryBackground() const;

};


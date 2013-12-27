#pragma once
#include <SFML/Graphics.hpp>

class InventoryGUI : public sf::Drawable {
public:

    // 
    void triggerInventoryGUI();

    void clearInventoryGUI();

    void toggleInventoryGUI();

    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    
    InventoryGUI(void);
    ~InventoryGUI(void);
    
    sf::RectangleShape *makeInventoryBackground() const;

    bool isVisible();

private: 
    
    static const int DEFAULT_INVENTORY_BORDER;
    static const int DEFAULT_INVENTORY_ITEMS_PER_COL;
    static const sf::Vector2i DEFAULT_INVENTORY_ENTRY_SIZE;
    static const int DEFAULT_INVENTORY_SPRITE_SEPARATION;
    static const int DEFAULT_INVENTORY_TEXT_SIZE;

    // Number of pixels between edges of inventory GUI and its contents.
    int inventoryBorder;

    // Number of items that should be displayed vertically in the inventory 
    // GUI.
    int inventoryItemsPerCol;

    // Size in pixels of a single entry in the inventory.
    sf::Vector2i inventoryEntrySize;

    // Number of pixels separating an item sprite and its name.
    int inventorySpriteSeparation;

    // Size of text in inventory.
    int inventoryTextSize;

    bool visible;
    int expectedInventorySize;

};


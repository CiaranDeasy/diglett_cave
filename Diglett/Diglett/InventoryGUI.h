#pragma once
#include <SFML/Graphics.hpp>

class InventoryGUI : sf::Drawable {
public:

    // 
    void triggerInventoryGUI();

    void clearInventoryGUI();

    void toggleInventoryGUI();

    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    
    InventoryGUI(void);
    ~InventoryGUI(void);
    
    static sf::Sprite *makeInventoryBackground( int x, int y );

private: 

    sf::Sprite *inventoryBackground;
    bool visible;
    int expectedInventorySize;

};


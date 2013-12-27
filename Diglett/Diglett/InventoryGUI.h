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
    
    static sf::RectangleShape *makeInventoryBackground();

    bool isVisible();

private: 

    bool visible;
    int expectedInventorySize;

};


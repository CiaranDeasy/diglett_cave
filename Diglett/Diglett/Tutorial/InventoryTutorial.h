#pragma once
#include <SFML/System.hpp>
#include "Tutorial.h"

class InventoryTutorial : public Tutorial {
public:
    InventoryTutorial();
    ~InventoryTutorial();

    // Returns true if the condition for this tutorial is satisfied.
    virtual bool testTrigger( World& world, Player& player );

    // Activates this tutorial.
    virtual void activate( GameWindow *gameWindow );

private:
    // The message displayed when this tutorial is activated.
    static const std::string message;
};


#pragma once
#include <SFML/System.hpp>
#include "GameWindow.h"

class Tutorial {
public:
    Tutorial();
    ~Tutorial();

    // Returns true if the condition for this tutorial is satisfied.
    virtual bool testTrigger() = 0;

    // Activates this tutorial.
    virtual void activate( GameWindow *gameWindow, sf::Font& font ) = 0;

    // Returns true if this tutorial has already been triggered.
    bool isTriggered();

protected:

    bool triggered;
};


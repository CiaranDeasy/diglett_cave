#pragma once
#include <SFML/System.hpp>
#include "Tutorial.h"
#include "World.h"

class OreTutorial : public Tutorial {
public:
    OreTutorial();
    ~OreTutorial();

    // Returns true if the condition for this tutorial is satisfied.
    virtual bool testTrigger( World& world );

    // Activates this tutorial.
    virtual void activate( GameWindow *gameWindow, sf::Font& font );

private:
    // The message displayed when this tutorial is activated.
    static const std::string message;
};


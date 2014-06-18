#pragma once
#ifndef ORE_TUTORIAL_H
#define ORE_TUTORIAL_H

#include <SFML/System.hpp>
#include "Tutorial.h"
#include "World.h"

class OreTutorial : public Tutorial {
public:
    OreTutorial();
    ~OreTutorial();

    // Returns true if the condition for this tutorial is satisfied.
    virtual bool testTrigger( World& world, Player& player );

    // Activates this tutorial.
    virtual void activate( GameWindow *gameWindow );

private:
    // The message displayed when this tutorial is activated.
    static const std::string message;
};

#endif // ORE_TUTORIAL_H

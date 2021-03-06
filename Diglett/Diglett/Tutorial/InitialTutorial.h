#pragma once
#ifndef INITIAL_TUTORIAL_H
#define INITIAL_TUTORIAL_H

#include <SFML/System.hpp>
#include "Tutorial.h"

class InitialTutorial : public Tutorial {
public:
    InitialTutorial();
    ~InitialTutorial();

    // Returns true if the condition for this tutorial is satisfied.
    virtual bool testTrigger( World& world, Player& player );

    // Activates this tutorial.
    virtual void activate( GameWindow *gameWindow );

private:
    // The message displayed when this tutorial is activated.
    static const std::string message;
};

#endif // INITIAL_TUTORIAL_H

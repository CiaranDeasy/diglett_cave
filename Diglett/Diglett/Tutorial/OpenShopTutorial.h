#pragma once
#ifndef OPEN_SHOP_TUTORIAL_H
#define OPEN_SHOP_TUTORIAL_H

#include <SFML/System.hpp>
#include "Tutorial.h"

class OpenShopTutorial : public Tutorial {
public:
    OpenShopTutorial();
    ~OpenShopTutorial();

    // Returns true if the condition for this tutorial is satisfied.
    virtual bool testTrigger( World& world, Player& player );

    // Activates this tutorial.
    virtual void activate( GameWindow *gameWindow );

private:
    // The message displayed when this tutorial is activated.
    static const std::string message;
};

#endif // OPEN_SHOP_TUTORIAL_H

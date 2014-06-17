#pragma once
#include <SFML/System.hpp>
#include <vector>
#include "Tutorial.h"
#include "GameWindow.h"

class TutorialHandler {
public:
    TutorialHandler( GameWindow *gameWindow );
    ~TutorialHandler();

    // Tests the tutorials' triggers to see if any have been triggered. 
    // If a tutorial has been triggered, it is activated. No more than one 
    // tutorial is activated by a single call to this method. Tutorials are 
    // deleted after activation, but not on the same call to testTriggers().
   void testTriggers( World& world, Player& player );

private:
    GameWindow *gameWindow;
    std::vector<Tutorial *> tutorials;

};


#include "TutorialHandler.h"
#include "InitialTutorial.h"
#include "OreTutorial.h"
#include "InventoryTutorial.h"

TutorialHandler::TutorialHandler( GameWindow *gameWindow, sf::Font& font ) 
        : font( font ) {
    this->gameWindow = gameWindow;
    tutorials = std::vector<Tutorial *>();
    tutorials.push_back( new InitialTutorial() );
    tutorials.push_back( new OreTutorial() );
    tutorials.push_back( new InventoryTutorial() );
}

TutorialHandler::~TutorialHandler() {
    // Cleanup the Tutorial objects on the heap.
    std::vector<Tutorial *>::iterator next = tutorials.begin();
    while( next != tutorials.end() ) {
        delete *next;
    }
};

void TutorialHandler::testTriggers( World& world ) {
    std::vector<Tutorial *>::iterator next = tutorials.begin();
    while( next != tutorials.end() ) {
        if( (*next)->isTriggered() ) {
            delete *next;
            next = tutorials.erase( next );
        }
        else if( (*next)->testTrigger( world ) ) {
            (*next)->activate( gameWindow, font );
            return; // Only want to activate one tutorial at most.
        } else {
            next++;
        }
    }
}

#include "TutorialHandler.h"
#include "InitialTutorial.h"
#include "OreTutorial.h"
#include "InventoryTutorial.h"
#include "OpenShopTutorial.h"

TutorialHandler::TutorialHandler( GameWindow *gameWindow ) {
    this->gameWindow = gameWindow;
    tutorials = std::vector<Tutorial *>();
    tutorials.push_back( new InitialTutorial() );
    tutorials.push_back( new OreTutorial() );
    tutorials.push_back( new InventoryTutorial() );
	tutorials.push_back( new OpenShopTutorial() );
}

TutorialHandler::~TutorialHandler() {
    // Cleanup the Tutorial objects on the heap.
    std::vector<Tutorial *>::iterator next = tutorials.begin();
    while( next != tutorials.end() ) {
        delete *next;
    }
};

void TutorialHandler::testTriggers( World& world, Player& player ) {
    std::vector<Tutorial *>::iterator next = tutorials.begin();
    while( next != tutorials.end() ) {
        if( (*next)->isTriggered() ) {
            delete *next;
            next = tutorials.erase( next );
        }
        else if( (*next)->testTrigger( world, player ) ) {
            (*next)->activate( gameWindow );
            return; // Only want to activate one tutorial at most.
        } else {
            next++;
        }
    }
}

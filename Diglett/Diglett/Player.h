#pragma once
#include <SFML/System.hpp>
#include <vector>
#include "Item.h"
#include "Inventory.h"

class Player {
public:
    static Player& getPlayer();

    ~Player(void);

    sf::Vector2f getPosition();
    void move( float x, float y );

    Inventory<Item *>& getInventory();

    // Increases the player's money by the specified amount. Negative input
    // decreases money. If money is decreased by an amount that would make it 
    // negative, no change is made, and the return value is false, otherwise 
    // returns true.
    bool addMoney( int amount );

    int getMaxHull();
    int getCurrentHull();

    // Decreases hull strength by the specified amount, stopping at zero.
    void damageHull( int damage );

private:
    static Player singleton;
    static const int DEFAULT_HULL = 150;

    // Values used to track the digging state.
    bool digging;
    sf::Vector2f diggingStepSize;
    int diggingStepsRemaining;
    sf::Vector2i diggingTowards;

    // Number of ticks the player has spent on the ground.
    int onGround;

    // The player's position is their centre. Adding a "Clip" to the 
    // appropriate component of the position gives a line of the player's 
    // bounding box.
    sf::Vector2f position;
    float topClip;
    float bottomClip;
    float leftClip;
    float rightClip;

    Inventory<Item *> inventory;
    int money;
    int maxHull;
    int currentHull;

    Player(void);

    // Sets the digging state and initialises the digging-related variables.
    void initiateDigging( sf::Vector2i target );

    // Moves the player towards the tile that they are digging. On the final 
    // step, unsets the digging state and updates variables appropriately.
    void processDiggingStep();
    
    // Tests whether the player is clipping with a tile in a given direction,
    // and tests for and triggers digging.
    bool clipLeft( float oldX, float oldY, float newX, float newY );
    bool clipRight( float oldX, float oldY, float newX, float newY );
    bool clipAbove( float oldX, float oldY, float newX, float newY );
    bool clipBelow( float oldX, float oldY, float newX, float newY );

};
#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System.hpp>
#include <vector>
#include "Item.h"
#include "Inventory.h"
#include "Direction.h"

class World;
class Player {
public:
    Player(void);
    ~Player(void);

    sf::Vector2f getPosition() const;
    void move( float x, float y, Direction directionOfInput, World& world );

    Inventory<Item *>& getInventory();

    int getMoney();

    // Increases the player's money by the specified amount. Negative input
    // decreases money. If money is decreased by an amount that would make it 
    // negative, no change is made, and the return value is false, otherwise 
    // returns true.
    bool addMoney( int amount );

    int getMaxHull();
    int getCurrentHull();

    // Decreases hull strength by the specified amount, stopping at zero.
    void damageHull( int damage );

    // Returns true if the player's hull is zero.
    bool isDead() const;

    // Restores the player's hull, empties their inventory, and resets their 
    // position.
    void respawn();

private:
    static const int DEFAULT_HULL = 150;
    static const int DEFAULT_MONEY = 0;

    // Number of ticks the player must spend on the ground before allowed to dig.
    static const int DIG_DELAY = 15;

    // Number of ticks it takes the player to dig a block.
#ifdef DIGLETT_DEBUG
    static const int DIG_STEPS = 15;
#else
    static const int DIG_STEPS = 60;
#endif

    // Values used to track the digging state.
    // True if the player is in the digging state.
    bool digging;
    // Distance to move the player per game tick while in the digging state.
    sf::Vector2f diggingStepSize;
    // Number of game ticks remaining before digging is complete.
    int diggingStepsRemaining;
    // The co-ordinates of the tile that the player is digging.
    sf::Vector2i diggingTowards;
    // A pointer to the world so the tile can be updated when the player
    // finishes digging it.
    World *worldToDig;

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

    // Sets the digging state and initialises the digging-related variables.
    void initiateDigging( sf::Vector2i target, World& world );

    // Moves the player towards the tile that they are digging. On the final 
    // step, unsets the digging state and updates variables appropriately.
    void processDiggingStep();
    
    // Tests whether the player is clipping with a tile in a given direction,
    // and tests for and triggers digging.
    bool clipLeft( float oldX, float oldY, float newX, float newY,
            Direction directionOfInput, World& world );
    bool clipRight( float oldX, float oldY, float newX, float newY,
            Direction directionOfInput, World& world );
    bool clipAbove( float oldX, float oldY, float newX, float newY,
            Direction directionOfInput, World& world );
    bool clipBelow( float oldX, float oldY, float newX, float newY,
            Direction directionOfInput, World& world );

};

#endif // PLAYER_H

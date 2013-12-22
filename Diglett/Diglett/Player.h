#pragma once
#include <SFML/System.hpp>
class Player {
public:
    static Player& getPlayer();
    sf::Vector2f getPosition();
    void move( float x, float y );
    // Number of ticks the player has spent on the ground.
    int onGround;
    ~Player(void);
private:
    enum Direction {
        North = 0,
        Northnortheast = 1,
        Northeast = 2,
        Eastnortheast = 3,
        East = 4,
        Eastsoutheast = 5,
        Southeast = 6,
        Southsoutheast = 7,
        South = 8,
        Southsouthwest = 9,
        Southwest = 10,
        Westsouthwest= 11,
        West = 12,
        Westnorthwest = 13,
        Northwest = 14,
        Northnorthwest = 15
    };
    static Player singleton;
    // Values used to track the digging state.
    bool digging;
    sf::Vector2f diggingStepSize;
    int diggingStepsRemaining;
    sf::Vector2i diggingTowards;
    // The player's position is their centre. Adding a "Clip" to the 
    // appropriate component of the position gives a line of the player's 
    // bounding box.
    sf::Vector2f position;
    float topClip;
    float bottomClip;
    float leftClip;
    float rightClip;
    Direction classifyDirectionOfMovement(
            float stickPositionX, float stickPositionY);
    void initiateDigging( sf::Vector2i target );
    void processDiggingStep();
    Player(void);
};
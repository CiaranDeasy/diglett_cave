#include "Physics.h"
#include "Player.h"
#include "Constants.h"

sf::Vector2f force;
float mass;
sf::Vector2f acceleration;
sf::Vector2f velocity;
sf::Vector2f previousLocation;

void Physics::updatePlayer(sf::Vector2f f){
    force = f;
    acceleration.x = f.x / PLAYER_MASS;
    acceleration.y = f.y / PLAYER_MASS;

    //Add gravitational force
    acceleration.y += -0.01;

    //Calculate current velocity
    velocity = (Player::getPlayer().getPosition() - previousLocation);

    //Apply constant air resistance
    //TODO: Make air resistance a funciton of velocity
    if ( velocity.x > 0 ) {
        acceleration.x -= 0.005;
    } else if ( velocity.x < 0 ) {
        acceleration.x += 0.005;
    }
    if ( velocity.y > 0 ) {
        acceleration.y -= 0.005;
    } else if ( velocity.y < 0 ) {
        acceleration.y += 0.005;
    }


    //set velocity to 0 if it is close enough that it should be
    if ( velocity.x < 0.001 && velocity.x > -0.001 ) {
        velocity.x = 0.0f;
    }
    if ( velocity.y < 0.001 && velocity.y > -0.001 ) {
        velocity.y = 0.0f;
    }

    //Update previous location
    previousLocation = Player::getPlayer().getPosition();

    //Apply acceleration
    velocity += acceleration;

    //Cap velocity at PLAYER_MAX_SPEED in both y and x directions
    if( velocity.x > PLAYER_MAX_SPEED ){
        velocity.x = PLAYER_MAX_SPEED;
    } else if ( velocity.x < -PLAYER_MAX_SPEED ){
        velocity.x = -PLAYER_MAX_SPEED;
    }
    if( velocity.y > PLAYER_MAX_SPEED ){
        velocity.y = PLAYER_MAX_SPEED;
    } else if ( velocity.y < -PLAYER_MAX_SPEED ){
        velocity.y = -PLAYER_MAX_SPEED;
    }

    //Move player
    Player::getPlayer().move(velocity.x, velocity.y);
    
}

Physics& Physics::getPhysics(){ return singleton; }

Physics Physics::singleton = Physics();

Physics::Physics(void){
    previousLocation = sf::Vector2f(1.0f,1.0f);
    mass = 1;
}
#include "Physics.h"
#include "Player.h"
#include "Constants.h"

sf::Vector2f force;
sf::Vector2f acceleration;
sf::Vector2f velocity;
sf::Vector2f previousLocation;

void Physics::updatePlayer(sf::Vector2f f){
    force = f;
    acceleration.x = f.x / PLAYER_MASS;
    acceleration.y = f.y / PLAYER_MASS;

    //Add gravitational force
    acceleration.y -= GRAVITY_STRENGTH;
    
    //Apply constant air resistance
    //TODO: Make air resistance a funciton of velocity
    if ( velocity.x != 0 ) {
        acceleration.x -= (HORIZONTAL_AIR_RESISTANCE * velocity.x);
    }
    /*if ( velocity.y > 0 ) {
        acceleration.y -= VERTICAL_AIR_RESISTANCE;
    } else if ( velocity.y < 0 ) {
        acceleration.y += VERTICAL_AIR_RESISTANCE;
    }*/


    //set velocity to 0 if it is close enough that it should be
    if ( f.x == 0 && velocity.x < MINIMUM_VELOCITY && velocity.x > -MINIMUM_VELOCITY ) {
        velocity.x = 0.0f;
        acceleration.x = 0.0f;
    }

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

void Physics::collideX() {
    velocity.x = 0;
}

void Physics::collideY() {
    velocity.y = 0;
}

void Physics::reset() {
    velocity.x = 0;
    velocity.y = 0;
}

Physics& Physics::getPhysics(){ return singleton; }

Physics Physics::singleton = Physics();

Physics::Physics(void){
    previousLocation = sf::Vector2f(1.0f,1.0f);
}
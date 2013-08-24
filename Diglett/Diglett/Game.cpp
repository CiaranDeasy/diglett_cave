#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "WorldData.h"
#include "Player.h"

sf::RenderWindow *window = NULL;

// For co-ordinate conversion from world co-ordinates to chunk co-ordinates, we
// need to always round towards negative infinity. C++ always rounds towards 
// zero. Today we correct that mistake.
int roundToMoreNegative( float f ) {
    if( f > 0 ) return (int) f;
    else return ( (int) f ) - 1;
}

// Converts a point in game co-ordinates to a tile index.
sf::Vector2i coordsGameToTile( sf::Vector2f in ) {
    return sf::Vector2i( roundToMoreNegative( in.x ), 
            roundToMoreNegative( in.y ) );
}

// Converts a point in game co-ordinates to a chunk index.
sf::Vector2i coordsGameToChunk( sf::Vector2f in ) {
    return sf::Vector2i( roundToMoreNegative( in.x / CHUNK_SIDE ), 
            roundToMoreNegative( in.y / CHUNK_SIDE ) );
}

// Converts a point in game co-ordinates to a point in window (drawing) 
// co-ordinates.
sf::Vector2f coordsGameToWindow( sf::Vector2f in ) {
    return sf::Vector2f( in.x * 64, in.y * -64 );
}

// Converts a tile index to a point in window (drawing) co-ordinates.
sf::Vector2f coordsTileToWindow( sf::Vector2i in ) {
    return coordsGameToWindow( sf::Vector2f( in.x, in.y ) );
}

// Constructs a square tile sprite of the specified color, with black outline.
sf::Sprite *makeSquareSprite( sf::Color color ) {
    // Make the render area.
    sf::RenderTexture renderer;
    renderer.create( PIXELS_PER_TILE, PIXELS_PER_TILE );
    renderer.clear();
    // Draw the outline.
    sf::RectangleShape outline( sf::Vector2f( PIXELS_PER_TILE, 
            PIXELS_PER_TILE ) );
    outline.setFillColor( sf::Color::Black );
    renderer.draw( outline );
    // Draw the filling colour over it.
    sf::RectangleShape fill( sf::Vector2f( PIXELS_PER_TILE - 2, 
            PIXELS_PER_TILE - 2 ) );
    fill.setFillColor( color );
    fill.move( 1.0f, 1.0f );
    renderer.draw( fill );
    // Make the sprite.
    renderer.display();
    sf::Texture texture = renderer.getTexture();
    // Copy the texture to the heap to prevent deallocation.
    // We can probably do something smarter than this at some point.
    sf::Texture *texturePointer = new sf::Texture( texture );
    return new sf::Sprite( *texturePointer );
}

// Constructs a circle sprite of the specified color.
sf::Sprite *makeCircleSprite( sf::Color color ) {
    // Make the render area.
    sf::RenderTexture renderer;
    renderer.create( PIXELS_PER_TILE, PIXELS_PER_TILE );
    renderer.clear( sf::Color::Transparent );
    
    // Draw the filling colour over it.
    sf::CircleShape circle( PIXELS_PER_TILE / 2 );
    circle.setFillColor( color );
    renderer.draw( circle );
    // Make the sprite.
    renderer.display();
    sf::Texture texture = renderer.getTexture();
    // Copy the texture to the heap to prevent deallocation.
    // We can probably do something smarter than this at some point.
    sf::Texture *texturePointer = new sf::Texture( texture );
    return new sf::Sprite( *texturePointer );
}

void init() {
    window = new sf::RenderWindow( 
            sf::VideoMode( WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y ), 
            WINDOW_TITLE );
	window->setFramerateLimit(60);
}

int main() {
    sf::View worldView( sf::Vector2f( 0.0f, 0.0f ), 
            sf::Vector2f( WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y ) );
    worldView.setViewport( sf::FloatRect( 0.0f, 0.0f, 1.0f, 1.0f ) );
    worldView.zoom( CAMERA_ZOOM );
    init();
    // Prepare the sprites.
    sf::Sprite *surfaceSprite = makeSquareSprite( sf::Color::Blue );
    sf::Sprite *dirtSprite = makeSquareSprite( sf::Color( 126, 64, 0, 255 ) );
    sf::Sprite *playerSprite = makeCircleSprite( sf::Color::Magenta );

    // Main loop.
    while( window->isOpen() ) {
        // Handle window events.
        sf::Event event;
        while( window->pollEvent( event ) ) {
            if( event.type == sf::Event::Closed ) {
                window->close();
                return 0;
            }
        }
        // Take player movement.
        // Keyboard
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
			Player::getPlayer().move( 0, PLAYER_SPEED );
        }
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) {
			Player::getPlayer().move( 0, -PLAYER_SPEED );
        }
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) {
			Player::getPlayer().move( -PLAYER_SPEED, 0 );
        }
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) {
			Player::getPlayer().move( PLAYER_SPEED, 0 );
        }
        // Controller
        float stickPositionX = 
            sf::Joystick::getAxisPosition( 0, sf::Joystick::X );
        float stickPositionY = 
            sf::Joystick::getAxisPosition( 0, sf::Joystick::Y );
		if( stickPositionX > CONTROLLER_DEADZONE || 
            stickPositionX < -CONTROLLER_DEADZONE ) {
			Player::getPlayer().move( 
                ( stickPositionX / 100 ) * PLAYER_SPEED, 0 );
		}
		if( stickPositionY > CONTROLLER_DEADZONE || 
            stickPositionY < -CONTROLLER_DEADZONE ) {
            Player::getPlayer().move( 
                0, ( stickPositionY / 100 ) * -PLAYER_SPEED );
		}
        // Draw the world.
        worldView.setCenter( coordsGameToWindow( 
            Player::getPlayer().getPosition() ) );
        window->setView( worldView );
        window->clear();
        sf::Vector2i playerChunk = coordsGameToChunk( 
            Player::getPlayer().getPosition() );
        for( int x = playerChunk.x - 1; x <= playerChunk.x + 1; x++ ) {
          for( int y = playerChunk.y - 1;  y <= playerChunk.y + 1; y++ ) {
            Chunk nextChunk = WorldData::getWorldData().getChunk( x, y );
            for( int i = 0; i < CHUNK_SIDE; i++ ) {
              for( int j = 0; j < CHUNK_SIDE; j++ ) {
                Tile nextTile = nextChunk.getTile( i, j );
                sf::Vector2i tilePosition = sf::Vector2i( 
                        nextChunk.getPosition().x + i,
                        nextChunk.getPosition().y + j );
                // Colour the origin red, for reference.
                if( tilePosition.x == 0 && tilePosition.y == 0 ) {
                    dirtSprite->setColor( sf::Color::Red );
                    dirtSprite->setPosition( 
                        coordsTileToWindow( tilePosition ) );
                    window->draw( *dirtSprite );
                    dirtSprite->setColor( sf::Color::White );
                }
                else if( nextTile.getType() == Tile::Dirt ) {
                    dirtSprite->setPosition( 
                        coordsTileToWindow( tilePosition ) );
                    window->draw( *dirtSprite );
                }
                else if( nextTile.getType() == Tile::Surface ) {
                    surfaceSprite->setPosition( 
                        coordsTileToWindow( tilePosition ) );
                    window->draw( *surfaceSprite );
                }
              }
            }
          }
        }
        playerSprite->setPosition( coordsGameToWindow( 
            Player::getPlayer().getPosition() ) );
        window->draw( *playerSprite );
        window->display();
	}
    return 0;
}
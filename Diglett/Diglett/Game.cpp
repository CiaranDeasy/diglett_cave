#include <iostream>
#include <SFML/Graphics.hpp>
#include "WorldData.h"
#include "Player.h"

const std::string WINDOW_TITLE = "Diglett";
const int PIXELS_PER_TILE = 64;
const float PLAYER_SPEED = 0.2;

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

int main() {
    // Create the initial objects.
    sf::RenderWindow window( sf::VideoMode( 800, 600 ), WINDOW_TITLE );
    sf::View worldView( sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 800, 600 ) );
    worldView.setViewport( sf::FloatRect( 0.0f, 0.0f, 1.0f, 1.0f ) );
    WorldData *worldData = new WorldData();
    Player *player = new Player();

    // Prepare the sprites.
    // Dirt sprite.
    sf::RenderTexture renderer;
    renderer.create( 64, 64 );
    renderer.clear();
    sf::RectangleShape outline( sf::Vector2f( 64.0f, 64.0f ) );
    outline.setFillColor( sf::Color::Black );
    sf::RectangleShape dirt( sf::Vector2f( 62.0f, 62.0f ) );
    dirt.setFillColor( sf::Color( 126, 64, 0, 255 ) );
    dirt.move( 1.0f, 1.0f );
    renderer.draw( outline );
    renderer.draw( dirt );
    renderer.display();
    sf::Texture dirtTexture = renderer.getTexture();
    sf::Sprite dirtSprite(dirtTexture);
	window.setFramerateLimit(60);

    // Main loop.
    while( window.isOpen() ) {
        // Handle window events.
        sf::Event event;
        while( window.pollEvent( event ) ) {
            if( event.type == sf::Event::Closed ) {
                window.close();
                return 0;
            }
        }
        // Take player movement.
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
			player->move( 0, PLAYER_SPEED );
        }
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) {
			player->move( 0, -PLAYER_SPEED );
        }
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) {
			player->move( -PLAYER_SPEED, 0 );
        }
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) {
			player->move( PLAYER_SPEED, 0 );
        }
        // Draw the world.
        worldView.setCenter( coordsGameToWindow( player->getPosition() ) );
        window.setView( worldView );
        window.clear();
        sf::Vector2i playerChunk = coordsGameToChunk( player->getPosition() );
        //std::cout << "PlayerChunk = " << playerChunk.x << "," << playerChunk.y 
        //        << "\n";
        for( int x = playerChunk.x - 1; x < playerChunk.x + 1; x++ ) {
            for( int y = playerChunk.y - 1;  y < playerChunk.y + 1; y++ ) {
                //std::cout << "getChunk( " << x << ", " << y << ")\n";
                Chunk nextChunk = worldData->getChunk( x, y );
                for( int i = 0; i < CHUNK_SIDE; i++ ) {
                    for( int j = 0; j < CHUNK_SIDE; j++ ) {
                        Tile nextTile = nextChunk.getTile( i, j );
                        sf::Vector2i tilePosition = sf::Vector2i( 
                                nextChunk.getPosition().x + i,
                                nextChunk.getPosition().y + j );
                        dirtSprite.setPosition( coordsTileToWindow( tilePosition ) );
                        if( tilePosition.x == 0 && tilePosition.y == 0 ) {
                            dirtSprite.setColor( sf::Color::Red );
                        }
                        else {
                            dirtSprite.setColor( sf::Color::White );
                        }
                        window.draw( dirtSprite );
                    }
                }
            }
        }
        window.display();
	}
    return 0;
}
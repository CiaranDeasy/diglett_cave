#include "GameWindow.h"
#include "Constants.h"
#include "WorldData.h"
#include "Player.h"
#include "Utility.h"
#include <sstream>

GameWindow *GameWindow::singleton = NULL;

GameWindow *GameWindow::getGameWindow() {
    if( singleton == NULL ) {
        singleton = new GameWindow();
    }
    return singleton;
}

void GameWindow::toggleDebugOverlay() {
    showDebugOverlay = !showDebugOverlay;
}

void GameWindow::createSprites() {
    tileSprites[Tile::Surface] = makeSquareSprite( sf::Color::Blue );
    tileSprites[Tile::Dirt] = makeSquareSprite( sf::Color( 126, 64, 0, 255 ) );
    tileSprites[Tile::Air] = makeSquareSprite( sf::Color( 156, 94, 0, 255 ) );
    playerSprite = makeCircleSprite( sf::Color::Magenta );
    playerSprite->setOrigin( 32, 32 );

}

// Constructs a square tile sprite of the specified color, with black outline.
sf::Sprite *GameWindow::makeSquareSprite( sf::Color color ) {
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
sf::Sprite *GameWindow::makeCircleSprite( sf::Color color ) {
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

void GameWindow::drawDebugOverlay() {
    sf::RenderTexture renderer;
    renderer.create( 120, 100 );
    renderer.clear( sf::Color( 0, 0, 0, 207 ) );

    sf::Text text;
    text.setFont( debugFont );
    float xPos = Player::getPlayer().getPosition().x;
    std::ostringstream o;
    o << "Player Position = \n(" << Player::getPlayer().getPosition().x 
        << ", " << Player::getPlayer().getPosition().y << ")";
    text.setString( o.str() );
    text.setCharacterSize( 12 );
    text.setColor( sf::Color::Blue );
    text.setPosition( 5, 5 );
    renderer.draw( text );
    renderer.display();
    sf::Texture texture = renderer.getTexture();
    sf::Texture debugOverlayTexture = sf::Texture( texture );
    sf::Sprite debugOverlay( debugOverlayTexture );
    debugOverlay.setPosition( -400, 200 );

    window->setView( interfaceView );
    window->draw( debugOverlay );
}

GameWindow::GameWindow(void) {
    window = new sf::RenderWindow( 
            sf::VideoMode( WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y ), 
            WINDOW_TITLE );
	window->setFramerateLimit(60);
    
    worldView = sf::View( sf::Vector2f( 0.0f, 0.0f ), 
            sf::Vector2f( WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y ) );
    worldView.setViewport( sf::FloatRect( 0.0f, 0.0f, 1.0f, 1.0f ) );
    worldView.zoom( CAMERA_ZOOM );
    
    interfaceView = sf::View( sf::Vector2f( 0.0f, 0.0f ), 
            sf::Vector2f( WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y ) );
    interfaceView.setViewport( sf::FloatRect( 0.0f, 0.0f, 1.0f, 1.0f ) );
    interfaceView.zoom( 1.0 );

    createSprites();

    if ( !debugFont.loadFromFile( DEBUG_FONT ) ) {
        std::cerr << "Failed to load font: " << DEBUG_FONT << "\n";
        exit(1);
    }
    showDebugOverlay = false;
}

GameWindow::~GameWindow(void) {
}

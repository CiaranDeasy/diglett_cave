#include "GameWindow.h"
#include "Constants.h"
#include "WorldData.h"
#include "Player.h"
#include "Utility.h"

GameWindow *GameWindow::singleton = NULL;

GameWindow *GameWindow::getGameWindow() {
    if( singleton == NULL ) {
        singleton = new GameWindow();
    }
    return singleton;
}

void GameWindow::createSprites() {
    tileSprites[Tile::Surface] = makeSquareSprite( sf::Color::Blue );
    tileSprites[Tile::Dirt] = makeSquareSprite( sf::Color( 126, 64, 0, 255 ) );
    tileSprites[Tile::Air] = makeSquareSprite( sf::Color( 156, 94, 0, 255 ) );
    playerSprite = makeCircleSprite( sf::Color::Magenta );

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

GameWindow::GameWindow(void) {
    window = new sf::RenderWindow( 
            sf::VideoMode( WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y ), 
            WINDOW_TITLE );
	window->setFramerateLimit(60);
    worldView = sf::View( sf::Vector2f( 0.0f, 0.0f ), 
            sf::Vector2f( WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y ) );
    worldView.setViewport( sf::FloatRect( 0.0f, 0.0f, 1.0f, 1.0f ) );
    worldView.zoom( CAMERA_ZOOM );
    createSprites();
}

GameWindow::~GameWindow(void) {
}

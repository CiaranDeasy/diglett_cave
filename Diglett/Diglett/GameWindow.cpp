#include "GameWindow.h"
#include "Constants.h"
#include "Tile.h"
#include "Item.h"
#include "MainGameState.h"

GameWindow::~GameWindow(void) {
}

GameWindow *GameWindow::singleton = NULL;

GameWindow *GameWindow::getGameWindow() {
    if( singleton == NULL ) {
        singleton = new GameWindow( 
            sf::VideoMode( WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y ), 
            WINDOW_TITLE );
    }
    return singleton;
}

sf::Sprite *GameWindow::makeSquareSprite( sf::Color color, int size ) {
    // Make the render area.
    sf::RenderTexture renderer;
    renderer.create( size, size );
    renderer.clear();
    // Draw the outline.
    sf::RectangleShape outline( sf::Vector2f( size, size ) );
    outline.setFillColor( sf::Color::Black );
    renderer.draw( outline );
    // Draw the filling colour over it.
    sf::RectangleShape fill( sf::Vector2f( size - 2, 
            size - 2 ) );
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

GameWindow::GameWindow( sf::VideoMode videoMode, std::string title ) :
            sf::RenderWindow( videoMode, title ),
            gameStates() {
	this->setFramerateLimit(60);

    Tile::initialiseTypes();
    Item::initialiseTypes();

    // Load a font to use for GUI text.
    if ( !font.loadFromFile( DEBUG_FONT ) ) {
        std::cerr << "Failed to load font: " << DEBUG_FONT << "\n";
        exit(1);
    }

    gameStates.push( new MainGameState( font, this ) );
}

void GameWindow::drawStateStack() {
    GameState *topState = gameStates.top();
    draw( *topState );
    if( topState->drawUnderlyingState() ) {
        gameStates.pop();
        drawStateStack();
        gameStates.push( topState );
    }
}
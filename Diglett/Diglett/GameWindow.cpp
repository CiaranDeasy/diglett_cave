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

void GameWindow::triggerNewItemVisual( Item *item ) {
    newItemVisuals.push_back( new NewItemVisual( font, item ) );
}

void GameWindow::createSprites() {
    playerSprite = makeCircleSprite( sf::Color::Magenta );
    playerSprite->setOrigin( 32, 32 );
    debugOverlayBackground = makeDebugOverlayBackground();
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

void GameWindow::toggleInventoryGUI() {
    inventoryGUI.toggle();
}

sf::Sprite *GameWindow::makeDebugOverlayBackground() {
    sf::RenderTexture renderer;
    renderer.create( 120, 100 );
    renderer.clear( sf::Color( 0, 0, 0, 207 ) );
    renderer.display();
    
    sf::Texture texture = renderer.getTexture();
    sf::Texture *texturePointer = new sf::Texture( texture );
    sf::Sprite* debugOverlay = new sf::Sprite( *texturePointer );
    debugOverlay->setPosition( -400, 200 );

    return debugOverlay;
}

void GameWindow::drawDebugOverlay() {

    sf::Text text;
    text.setFont( font );
    float xPos = Player::getPlayer().getPosition().x;
    std::ostringstream o;
    o << "Player Position = \n(" << Player::getPlayer().getPosition().x 
        << ", " << Player::getPlayer().getPosition().y << ")";
    text.setString( o.str() );
    text.setCharacterSize( 12 );
    text.setColor( sf::Color::White);
    text.setPosition( -395, 205 );

    window->setView( interfaceView );
    window->draw( *debugOverlayBackground );
    window->draw( text );
}

GameWindow::GameWindow(void) : 
            inventoryGUI( font, Player::getPlayer().getInventory() ), 
            hullGUI( font ) {
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
    Tile::initialiseTypes();
    Item::initialiseTypes();

    // Load a font to use for GUI text.
    if ( !font.loadFromFile( DEBUG_FONT ) ) {
        std::cerr << "Failed to load font: " << DEBUG_FONT << "\n";
        exit(1);
    }

    showDebugOverlay = false;
}

GameWindow::~GameWindow(void) {
}

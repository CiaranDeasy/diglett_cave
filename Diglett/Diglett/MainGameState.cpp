#include "MainGameState.h"
#include "Physics.h"
#include "GameWindow.h"
#include "Utility.h"
#include "WorldData.h"
#include <sstream>

MainGameState::MainGameState( sf::Font& font, GameWindow *gameWindow ) : 
        GameState(),
        font( font ), 
        inventoryGUI( font, Player::getPlayer().getInventory() ),
        hullGUI( font ), 
        inputHandler( *this ) {
    createSprites();
    showDebugOverlay = false;
    this->gameWindow = gameWindow;
    expectedInventorySize = 
            Player::getPlayer().getInventory().getCurrentSize();
}

MainGameState::~MainGameState() {
}

void MainGameState::setInterfaceView( sf::RenderTarget& target ) {
    sf::View interfaceView = sf::View( sf::FloatRect( 
            0, 0, target.getSize().x, target.getSize().y ) );
    target.setView( interfaceView );
}

void MainGameState::setWorldView( sf::RenderTarget& target ) {
    sf::Vector2f centerPoint = 
        ( Utility::coordsGameToWindow( Player::getPlayer().getPosition() ) );
    sf::View worldView = sf::View( centerPoint, 
            sf::Vector2f( target.getSize().x, target.getSize().y ) );
    worldView.zoom( CAMERA_ZOOM );
    target.setView( worldView );
}

void MainGameState::gameTick() {
    // Pass window events to the InputHandler.
    handleWindowEvents();
    // Process the player's input.
    inputHandler.processInputs();
    // Create NewItemVisuals.
    triggerNewItemVisuals();
    // Age the NewItemVisuals, and clean up any dead ones.
    std::vector<NewItemVisual *>::iterator next = 
         newItemVisuals.begin();
    while( next != newItemVisuals.end() ) {
        if( (*next)->isAlive() ) {
            (*next)->tick();
            next++;
        } else {
            // Cleanup dead NewItemVisuals.
            delete *next;
            next = newItemVisuals.erase( next );
        }
    }
}
    
void MainGameState::draw( 
        sf::RenderTarget& target, 
        sf::RenderStates states ) const {
    drawWorld( target );
    drawPlayer( target );
    drawGUI( target );
}

bool MainGameState::drawUnderlyingState() { return false; }

void MainGameState::toggleDebugOverlay() {
    showDebugOverlay = !showDebugOverlay;
}

void MainGameState::triggerNewItemVisuals() {
    // Check if the player's inventory grew.
    int currentInventorySize = 
            Player::getPlayer().getInventory().getCurrentSize();
    if( currentInventorySize > expectedInventorySize ) {
        Item *item = Player::getPlayer().getInventory().getContents()
                [currentInventorySize - 1];
        newItemVisuals.push_back( new NewItemVisual( font, item ) );
    }
    expectedInventorySize = currentInventorySize;
}

void MainGameState::toggleInventoryGUI() {
    inventoryGUI.toggle();
}

void MainGameState::createSprites() {
    playerSprite = GameWindow::makeCircleSprite( sf::Color::Magenta );
    playerSprite->setOrigin( 32, 32 );
    playerDeadSprite = GameWindow::makeCircleSprite( sf::Color::Red );
    playerDeadSprite->setOrigin( 32, 32 );
    debugOverlayBackground = makeDebugOverlayBackground();
}

sf::Sprite *MainGameState::makeDebugOverlayBackground() {
    sf::RenderTexture renderer;
    renderer.create( 120, 100 );
    renderer.clear( sf::Color( 0, 0, 0, 207 ) );
    renderer.display();
    
    sf::Texture texture = renderer.getTexture();
    sf::Texture *texturePointer = new sf::Texture( texture );
    sf::Sprite* debugOverlay = new sf::Sprite( *texturePointer );

    return debugOverlay;
}

void MainGameState::drawDebugOverlay( sf::RenderTarget& target ) const {
    sf::Text text;
    text.setFont( font );
    float xPos = Player::getPlayer().getPosition().x;
    std::ostringstream o;
    o << "Player Position = \n(" << Player::getPlayer().getPosition().x 
        << ", " << Player::getPlayer().getPosition().y << ")";
    text.setString( o.str() );
    text.setCharacterSize( 12 );
    text.setColor( sf::Color::White);
    text.setPosition( 5, WINDOW_RESOLUTION.y - 95 );

    debugOverlayBackground->setPosition( 0, WINDOW_RESOLUTION.y - 100 );
    target.draw( *debugOverlayBackground );
    target.draw( text );
}

void MainGameState::handleWindowEvents() {
    sf::Event event = sf::Event();
    while( gameWindow->pollEvent( event ) ) {
        if( event.type == sf::Event::Closed ) {
            gameWindow->close();
            exit(0);
        }
        if( event.type == sf::Event::JoystickButtonPressed ||
            event.type == sf::Event::KeyPressed ) {
            inputHandler.addEvent( event );
        }
    }
}

void MainGameState::drawWorld( sf::RenderTarget& target ) const {
    setWorldView( target );
    target.clear();
    sf::Vector2i playerChunk = Utility::coordsGameToChunk( 
        Player::getPlayer().getPosition() );
    for( int x = playerChunk.x - 1; x <= playerChunk.x + 1; x++ ) {
      for( int y = playerChunk.y - 1;  y <= playerChunk.y + 1; y++ ) {
        Chunk nextChunk = WorldData::getWorldData().getChunk( x, y );
        for( int i = 0; i < CHUNK_SIDE; i++ ) {
          for( int j = 0; j < CHUNK_SIDE; j++ ) {
            Tile nextTile = nextChunk.getRelativeTile( i, j );
            sf::Vector2i tilePosition = sf::Vector2i( 
                    nextChunk.getPosition().x + i,
                    nextChunk.getPosition().y + j );
            nextTile.getSprite()->setPosition( 
                Utility::coordsTileToWindow( tilePosition ) );
            target.draw( *nextTile.getSprite() );
          }
        }
      }
    }
}

void MainGameState::drawPlayer( sf::RenderTarget& target ) const {
    setWorldView( target );
    if( Player::getPlayer().isDead() ) {
       playerDeadSprite->setPosition( Utility::coordsGameToWindow( 
              Player::getPlayer().getPosition() ) );
       target.draw( *playerDeadSprite );
    } else {
       playerSprite->setPosition( Utility::coordsGameToWindow( 
              Player::getPlayer().getPosition() ) );
       target.draw( *playerSprite );
    }
}

void MainGameState::drawGUI( sf::RenderTarget& target ) const {
    setInterfaceView( target );
    if( showDebugOverlay ) {
        drawDebugOverlay( target );
    }
    if( inventoryGUI.isVisible() ) {
        target.draw( inventoryGUI );
    }
    // Display the NewItemVisuals.
    std::vector<NewItemVisual *>::const_iterator next = newItemVisuals.begin();
    while( next != newItemVisuals.end() ) {
        if( (*next)->isAlive() ) {
            target.draw(**next);
            next++;
        } else next++;
    }
    // Display the hull strength GUI.
    target.draw( hullGUI );
}

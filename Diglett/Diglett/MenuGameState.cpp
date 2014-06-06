#include "MenuGameState.h"
#include "Player.h"
#include "Physics.h"
#include "MainGameState.h"

const std::string MenuGameState::SPRITE_FILE = "Sprites/Logo.png";

MenuGameState::MenuGameState( 
            GameWindow *gameWindow, sf::Font& font ) : 
        inputHandler( *this ), 
        player( player ),
		font( font ) {
    this->gameWindow = gameWindow;

	// Create the logo.
    logoTexture = new sf::Texture();
    if ( !logoTexture->loadFromFile( SPRITE_FILE ) ) {
        std::cerr << "Failed to load file: " << SPRITE_FILE << "\n";
        exit(1);
    }
    logoSprite = new sf::Sprite();
    this->logoSprite->setTexture( *logoTexture );
    sf::FloatRect bounds = logoSprite->getLocalBounds();
    logoSprite->setOrigin( bounds.left + bounds.width / 2, 
            bounds.top + bounds.height / 2 );
    logoSprite->setPosition( 
		    gameWindow->getSize().x / 2, gameWindow->getSize().y / 4 );

	// Create the text.
	text = new sf::Text();
	text->setString( "Press SPACE or Gamepad A to begin." );
	text->setFont( font );
	text->setPosition( 
		    gameWindow->getSize().x / 2, 3 * gameWindow->getSize().y / 4 );
	text->setColor( sf::Color::White );
	bounds = text->getLocalBounds();
	text->setOrigin( bounds.left + bounds.width / 2, 
            bounds.top + bounds.height / 2 );
}

MenuGameState::~MenuGameState() {
}

void MenuGameState::gameTick() {
    handleWindowEvents();
    inputHandler.processInputs();
}

void MenuGameState::draw(sf::RenderTarget& target, sf::RenderStates states) 
        const {
    setInterfaceView( target );

	// Draw the background.
	sf::RectangleShape background = sf::RectangleShape( 
		    sf::Vector2f( target.getSize().x, target.getSize().y ) );
	background.setFillColor( sf::Color( 156, 94, 0, 255 ) );
	target.draw( background, states );

    // Draw the logo.
	logoSprite->setPosition( target.getSize().x / 2, target.getSize().y / 4 );
	target.draw( *logoSprite, states );

	// Draw the text.
	text->setPosition( target.getSize().x / 2, 3 * target.getSize().y / 4 );
	target.draw( *text, states );
}

bool MenuGameState::drawUnderlyingState() { return false; }

void MenuGameState::handleWindowEvents() {
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

void MenuGameState::launchGame() {
	gameWindow->pushNewState( new MainGameState( font, gameWindow ) );
}


MenuGameState::MenuInputHandler::MenuInputHandler( MenuGameState& gameState ) :
        gameState( gameState ) {
}
MenuGameState::MenuInputHandler::~MenuInputHandler() {
}

void MenuGameState::MenuInputHandler::processInputs() {
    std::vector<sf::Event>::const_iterator next = 
         buttonsPressed.begin();
    while( next != buttonsPressed.end() ) {
        if( next->type == sf::Event::JoystickButtonPressed && 
                next->joystickButton.button == 0 ) {
            gameState.launchGame();
        } else if( next->type == sf::Event::KeyPressed && 
                next->key.code == sf::Keyboard::Space ) {
            gameState.launchGame();
        }
        next++;
    }
}

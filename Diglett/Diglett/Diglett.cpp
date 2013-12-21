// Deprecated
// This file contains some early experimentation with the SFML library, and 
// is not part of the main project.

#include <iostream>
#include <SFML/Graphics.hpp>

const float DIGLETT_SPEED = 3.f;

int not_main() {
	sf::View full( sf::FloatRect( 0.f, 0.f, 200.f, 200.f ) );
	sf::View mini( sf::FloatRect( 0.f, 0.f, 200.f, 200.f ) );
	full.setViewport( sf::FloatRect( 0.f, 0.f, 1.f, 1.f ) );
	mini.setViewport( sf::FloatRect( 0.75f, 0.f, 0.25f, 0.25f ) );
	std::cout << "Use the up and down arrows to move the Diglett!!!\n";
	std::cout << "Or use the left analog stick! CONTROLLER SUPPORT!!!!!\n";
    sf::RenderWindow window( sf::VideoMode( 200, 200 ), "Diglett" );
	sf::RenderTexture rawDiglett;
	rawDiglett.create(200, 200);
	rawDiglett.clear();
    sf::CircleShape head( 100.f );
	sf::RectangleShape body( sf::Vector2f( 200.f,100.f ) );
	sf::CircleShape nose( 10.f );
	sf::CircleShape leftEye(25.f);
	sf::CircleShape rightEye(25.f);
	body.move( 0.f, 100.f );
	nose.move( 100.f, 100.f );
	nose.setOrigin( 10.f, 10.f );
	nose.scale( 3.f, 1.f );
	leftEye.move(67.f, 60.f);
	leftEye.setOrigin(30.f, 30.f);
	leftEye.scale(0.2f, 1.f);
	rightEye.move(133.f, 60.f);
	rightEye.setOrigin(30.f, 30.f);
	rightEye.scale(0.2f, 1.f);
    head.setFillColor( sf::Color( 126, 64, 0, 255 ) );
    body.setFillColor( sf::Color( 126, 64, 0, 255 ) );
    nose.setFillColor( sf::Color( 255, 128, 160, 255 ) );
	leftEye.setFillColor( sf::Color(0,0,0,255) );
	rightEye.setFillColor( sf::Color(0,0,0,255) );
    rawDiglett.draw( head );
    rawDiglett.draw( body );
    rawDiglett.draw( nose );
	rawDiglett.draw(leftEye);
	rawDiglett.draw(rightEye);
	rawDiglett.display();
	sf::Texture diglettTexture= rawDiglett.getTexture();
	sf::Sprite diglett(diglettTexture);
	window.setFramerateLimit(60);

    while( window.isOpen() ) {
        sf::Event event;
        while( window.pollEvent( event ) ) {
            if( event.type == sf::Event::Closed )
                window.close();
        }
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down )
			   && diglett.getPosition().y < 200 ) {
			diglett.move( 0, DIGLETT_SPEED );
        }
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) 
			   && diglett.getPosition().y > 0 ) {
			diglett.move( 0, -DIGLETT_SPEED );
        }
		float stickPosition = sf::Joystick::getAxisPosition( 0, sf::Joystick::Y );
		if( stickPosition > 20 && diglett.getPosition().y < 200 ) {
			diglett.move( 0, ( stickPosition / 100 ) * DIGLETT_SPEED );
		}
		else if( stickPosition < -20 && diglett.getPosition().y > 0 ) {
			diglett.move( 0, ( stickPosition / 100 ) * DIGLETT_SPEED );
		}
        window.clear();
		window.setView(full);
		window.draw(diglett);
		window.setView(mini);
		window.draw(diglett);
        window.display();
    }	
	return -1;
}

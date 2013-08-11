#include <iostream>
#include <SFML/Graphics.hpp>

const float DIGLETT_SPEED = 3.f;

int main() {
	std::cout << "Use the up and down arrows to move the Diglett!!!\n";
	std::cout << "Or use the left analog stick! CONTROLLER SUPPORT!!!!!\n";
    sf::RenderWindow window( sf::VideoMode( 200, 200 ), "Diglett" );
	sf::RenderTexture rawDiglett;
	rawDiglett.create(200, 200);
	rawDiglett.clear();
    sf::CircleShape head( 100.f );
	sf::RectangleShape body( sf::Vector2f( 200.f,100.f ) );
	sf::CircleShape nose( 10.f );
	body.move( 0.f, 100.f );
	nose.move( 100.f, 75.f );
	nose.setOrigin( 10.f, 10.f );
	nose.scale( 3.f, 1.f );
    head.setFillColor( sf::Color( 126, 64, 0, 255 ) );
    body.setFillColor( sf::Color( 126, 64, 0, 255 ) );
    nose.setFillColor( sf::Color( 255, 128, 160, 255 ) );
    rawDiglett.draw( head );
    rawDiglett.draw( body );
    rawDiglett.draw( nose );
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
		window.draw(diglett);
        window.display();
    }	
}

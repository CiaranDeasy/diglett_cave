#include <iostream>
#include <SFML/Graphics.hpp>

const std::string WINDOW_TITLE = "Diglett";

int main() {
    sf::RenderWindow window( sf::VideoMode( 800, 600 ), WINDOW_TITLE );
    while( window.isOpen() ) {
        sf::Event event;
        while( window.pollEvent( event ) ) {
            if( event.type == sf::Event::Closed )
                window.close();
        }
        window.clear();
	}
}
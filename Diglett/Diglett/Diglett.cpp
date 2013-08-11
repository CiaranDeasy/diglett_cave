#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
	std::cout << "hello, world!\n";
    sf::RenderWindow window(sf::VideoMode(200, 200), "Diglett");
    sf::CircleShape shape(100.f);
	sf::RectangleShape square(sf::Vector2f(200.f,100.f));
	sf::CircleShape nose(10.f);
	square.move(0.f, 100.f);
	nose.move(100.f, 75.f);
	nose.setOrigin(10.f, 10.f);
	nose.scale(3.f, 1.f);
    shape.setFillColor(sf::Color(126, 64, 0, 255));
    square.setFillColor(sf::Color(126, 64, 0, 255));
    nose.setFillColor(sf::Color(255, 128, 160, 255));
//HEllo

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(square);
        window.draw(nose);
        window.display();
    }
}

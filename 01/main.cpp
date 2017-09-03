#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "title");

    window.clear();

    sf::CircleShape shape1(40);
    shape1.setPosition({200, 120});
    shape1.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape1);

    sf::CircleShape shape2(48);
    shape2.setPosition({260, 120});
    shape2.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape2);

    sf::CircleShape shape3(60);
    shape3.setPosition({320, 160});
    shape3.setFillColor(sf::Color(0x0, 0x0, 0xFF));
    window.draw(shape3);

    sf::CircleShape shape4(75);
    shape4.setPosition({330, 220});
    shape4.setFillColor(sf::Color(0xFF, 0xFF, 0x0));
    window.draw(shape4);

    window.display();

    sf::sleep(sf::seconds(5));
}

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    const sf::Vector2f speed = { 20.f, 10.f };

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Moving Ball");
    sf::Clock clock;

    sf::CircleShape shape(40);
    shape.setPosition({ 200, 120 });
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float dt = clock.restart().asSeconds();

        sf::Vector2f position = shape.getPosition();
        position += speed * dt;
        shape.setPosition(position);

        window.clear();
        window.draw(shape);
        window.display();
    }
}

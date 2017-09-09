#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>

void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(sf::ConvexShape &shape, const sf::Event::MouseMoveEvent &event)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

    const sf::Vector2f mousePosition = {float(event.x), float(event.y)};
    const sf::Vector2f delta = mousePosition - shape.getPosition();
    const float angle = atan2(delta.y, delta.x);
    shape.setRotation(toDegrees(angle));
}

void pollEvents(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(pointer, event.mouseMove);
            break;
        }
    }
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Pointer follows mouse");
    sf::Clock clock;

    sf::ConvexShape pointer;
    init(pointer);

    while (window.isOpen())
    {
        // 1. process events
        pollEvents(window, pointer);

        // 2. update
        const float dt = clock.restart().asSeconds();

        // 3. redraw
        window.clear();
        window.draw(pointer);
        window.display();
    }
}

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

sf::Vector2f getBallOffset(float time)
{
    constexpr float speedX = 100.f;
    constexpr float amplitudeY = 80.f;
    constexpr float periodY = 2;

    const float x = speedX * time;
    const float wavePhase = time * float(2 * M_PI);
    const float y = amplitudeY * std::sin(wavePhase / periodY);

    return { x, y };
}

sf::Vector2f invertY(const sf::Vector2f& value)
{
    return { value.x, -value.y };
}

int main()
{
    constexpr float BALL_SIZE = 40;

    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Sinusoid Motion");
    sf::Clock clock;

    const sf::Vector2f position1 = { 10, 250 };
    const sf::Vector2f position2 = { 10, 350 };

    sf::CircleShape ball1(BALL_SIZE);
    ball1.setFillColor(sf::Color(0x80, 0x20, 0xFF));

    sf::CircleShape ball2(BALL_SIZE);
    ball2.setFillColor(sf::Color(0xFF, 0xFF, 0x20));

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

        const float time = clock.getElapsedTime().asSeconds();
        ball1.setPosition(position1 + getBallOffset(time));
        ball2.setPosition(position2 + invertY(getBallOffset(time)));

        window.clear();
        window.draw(ball1);
        window.draw(ball2);
        window.display();
    }
}

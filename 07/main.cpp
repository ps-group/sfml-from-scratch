#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr float BALL_RADIUS = 40;
constexpr unsigned FPS_LIMIT = 60;

void pollEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void update(sf::Clock& clock, sf::CircleShape& shape, sf::Vector2f& speed)
{
    const float dt = clock.restart().asSeconds();

    sf::Vector2f position = shape.getPosition();
    position += speed * dt;

    if ((position.x + 2 * BALL_RADIUS >= WINDOW_WIDTH) && (speed.x > 0))
    {
        speed.x = -speed.x;
    }
    if ((position.x < 0) && (speed.x < 0))
    {
        speed.x = -speed.x;
    }
    if ((position.y + 2 * BALL_RADIUS >= WINDOW_HEIGHT) && (speed.y > 0))
    {
        speed.y = -speed.y;
    }
    if ((position.y < 0) && (speed.y < 0))
    {
        speed.y = -speed.y;
    }

    shape.setPosition(position);
}

void draw(sf::RenderWindow& window, const sf::CircleShape& shape)
{
    window.clear();
    window.draw(shape);
    window.display();
}

// Ожидает времени следующего кадра с учётом ограничения FPS
void waitNextFrameTime(sf::Clock& clock)
{
    // Вычисляем длительность кадра и минимальную длительность ожидания.
    constexpr float FRAME_PERIOD_SECONDS = 1.0f / float(FPS_LIMIT);
    constexpr float MIN_WAIT_SECONDS = 0.001f;

    // Вычисляем время с предыдущего кадра и время до следующего кадра.
    const float deltaSeconds = clock.restart().asSeconds();
    const float secondsBeforeNextFrame = FRAME_PERIOD_SECONDS - deltaSeconds;

    // Спим, если до следующего кадра осталось достаточно много времени.
    if (secondsBeforeNextFrame > MIN_WAIT_SECONDS)
    {
        sf::sleep(sf::seconds(secondsBeforeNextFrame));
    }
}

int main()
{

    // Создаём окно с параметрами сглаживания
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ 800, 600 }), "FPS limited to " + std::to_string(FPS_LIMIT),
        sf::Style::Default, settings);
    sf::Clock updateClock;
    sf::Clock frameClock;

    sf::CircleShape shape(BALL_RADIUS);
    shape.setPosition({ 200, 120 });
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    sf::Vector2f speed = { 100.f, 100.f };

    while (window.isOpen())
    {
        pollEvents(window);
        update(updateClock, shape, speed);
        draw(window, shape);
        waitNextFrameTime(frameClock);
    }
}

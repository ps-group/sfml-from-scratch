#include "RussianFlag.h"
#include <SFML/Graphics.hpp>
#include <string>

// Функция создаёт окно определённого размера с определённым заголовком.
void initWindow(sf::RenderWindow& window)
{
    sf::VideoMode videoMode(800, 600);
    const std::string title = "Russian Flag + class derived from sf::Drawable";
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(videoMode, title, sf::Style::Default, settings);
}

int main()
{
    sf::RenderWindow window;
    initWindow(window);

    RussianFlag flag({100, 50}, {300, 150});

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
        // Рисуем flag как обычную фигуру или спрайт: вызовом window.draw.
        window.clear();
        window.draw(flag);
        window.display();
    }
}

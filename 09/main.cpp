#include "HeroPuppeteer.h"
#include <SFML/Graphics.hpp>

constexpr unsigned WINDOW_WIDHT = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

// Функция создаёт окно определённого размера с определённым заголовком.
void createWindow(sf::RenderWindow& window)
{
    sf::VideoMode videoMode(WINDOW_WIDHT, WINDOW_HEIGHT);
    const std::string title = "Controlling Hero: Animated Sprite + Puppeteer";
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    window.create(videoMode, title, sf::Style::Default, settings);
}

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

void update(sf::Clock& clock, HeroPuppeteer& puppeteer)
{
	float dt = clock.restart().asSeconds();
	puppeteer.update(dt);
}

void drawFrame(sf::RenderWindow& window, AnimatedSprite& heroSprite)
{
    // Рисуем анимированный спрайт как обычный спрайт: вызовом window.draw.
    window.clear(sf::Color(0x20, 0x20, 0x20));
    window.draw(heroSprite);
    window.display();
}

int main()
{
	sf::RenderWindow window;
	createWindow(window);

	sf::Clock clock;

	AnimatedSprite heroSprite;
	if (!heroSprite.loadFromFiles("man_hero.png", "man_hero.atlas"))
	{
		return 1;
	}
	heroSprite.setPosition({0.1f * float(WINDOW_WIDHT), 0.9f * float(WINDOW_HEIGHT)});

	HeroPuppeteer heroPuppeteer(heroSprite);
	while (window.isOpen())
	{
		pollEvents(window);
		update(clock, heroPuppeteer);
		drawFrame(window, heroSprite);
	}
}

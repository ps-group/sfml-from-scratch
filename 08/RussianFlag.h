#pragma once
#include <SFML/Graphics.hpp>

// Класс RussianFlag рисует флаг России.
// Наследуем его от sf::Drawable, чтобы можно было рисовать флаг проще:
//  window.draw(flag);
class RussianFlag : public sf::Drawable
{
public:
	// Конструктор принимает два параметра: положение и размер флага.
	RussianFlag(const sf::Vector2f& position, const sf::Vector2f& size);

private:
	// Метод draw вызывается окном при рисовании флага,
	//  то есть window.draw(flag) косвенно привозит к вызову этого метода.
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::RectangleShape m_whiteStrip;
	sf::RectangleShape m_blueStrip;
	sf::RectangleShape m_redStrip;
};

#include "RussianFlag.h"

RussianFlag::RussianFlag(const sf::Vector2f& position, const sf::Vector2f& size)
{
    const sf::Vector2f stripSize = { size.x, size.y / 3.f };

    m_whiteStrip.setSize(stripSize);
    m_whiteStrip.setPosition(position);
    m_whiteStrip.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    m_blueStrip.setSize(stripSize);
    m_blueStrip.setPosition(position + sf::Vector2f{ 0.f, stripSize.y });
    m_blueStrip.setFillColor(sf::Color(0, 0, 0xFF));

    m_redStrip.setSize(stripSize);
    m_redStrip.setPosition(position + sf::Vector2f{ 0.f, 2.f * stripSize.y });
    m_redStrip.setFillColor(sf::Color(0xFF, 0, 0));
}

void RussianFlag::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_whiteStrip, states);
    target.draw(m_blueStrip, states);
    target.draw(m_redStrip, states);
}

#include "HeroPuppeteer.h"
#include <cmath>
#include <float.h>
#include <cassert>
#include <iostream>

// Скорость персонажа, пикселей в секунду.
constexpr float HERO_SPEED = 100.f;

constexpr float JUMP_START_SPEED = 250.f;

// Ускорение свободного падения, пикселей в секунду.
const sf::Vector2f GRAVITY_ACCELERATION = {0, 800.f};

// Длительность кадра анимации, в секундах.
constexpr float FRAME_DURATION = 0.1f;

static float length(const sf::Vector2f& value)
{
    return std::hypotf(value.x, value.y);
}

static sf::Vector2f normalize(const sf::Vector2f& value)
{
    const float valueLength = length(value);
    if (valueLength < FLT_EPSILON)
    {
        return { 0, 0 };
    }
    return value / valueLength;
}

HeroPuppeteer::HeroPuppeteer(AnimatedSprite& sprite)
    : m_sprite(sprite)
{
}

void HeroPuppeteer::update(float dt)
{
    switch (m_state)
    {
    case State::NotStarted:
    case State::Idle:
    case State::Walking:
        updateIdleOrWalking(dt);
        break;
    case State::Jumping:
        updateJumping(dt);
        break;
    }

    if (m_updateAnimation)
    {
        m_updateAnimation(dt);
    }
}

void HeroPuppeteer::updateIdleOrWalking(float dt)
{
    // Герой двигается, влево, вправо либо стоит на месте.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        m_sprite.setScale(-1, 1);
        m_speed.x = -HERO_SPEED;
        switchState(State::Walking);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        m_sprite.setScale(1, 1);
        m_speed.x = HERO_SPEED;
        switchState(State::Walking);
    }
    else
    {
        m_speed = { 0, 0 };
        switchState(State::Idle);
    }

    // Герой начинает прыжок.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        m_jumpStartY = m_sprite.getPosition().y;
        m_speed.y = -JUMP_START_SPEED;
        switchState(State::Jumping);
    }

    // Передвигаем куклу-персонажа.
    m_sprite.setPosition(m_sprite.getPosition() + m_speed * dt);
}

void HeroPuppeteer::updateJumping(float dt)
{
    // NOTE: Мы завершаем прыжок в момент, когда текущее значение коодинаты Y
    //  стало больше или равно, чем значение до прыжка (т.к. ось Oy направлена вниз).
    // Если в игре есть физическая система, то лучше реагировать на столкновение.

    // Применяем ускорение к скорости.
    m_speed += GRAVITY_ACCELERATION * dt;

    // Проверяем, не завершился ли прыжок.
    sf::Vector2f newPosition = m_sprite.getPosition() + m_speed * dt;
    if (newPosition.y >= m_jumpStartY)
    {
        // Приземляем персонажа и сбрасываем скорость
        newPosition.y = m_jumpStartY;
        m_speed = { 0, 0 };

        // Меняем состояние.
        switchState(State::Idle);
    }
    // Передвигаем куклу-персонажа.
    m_sprite.setPosition(newPosition);
}

void HeroPuppeteer::switchState(State state)
{
    if (m_state == state)
    {
        // Состояние не изменилось - эффекта перехода нет.
        return;
    }

    // Запускаем анимацию либо выставляем статичный кадр.
    switch (state)
    {
    case State::NotStarted:
        // Нельзя переключаться на состояние NotStarted.
        assert(!"cannot switch to NotStarted");
        break;

    case State::Idle:
        // Проверяем, каким было прошлое состояние.
        if (m_state == State::Jumping)
        {
            // Включаем анимацию приземления
            m_updateAnimation = m_sprite.startAnimation(FRAME_DURATION, {
                "hero_jump_2.png",
                "hero_idle_0.png"
            });
        }
        else
        {
            m_sprite.selectFrame("hero_idle_0.png");
            m_updateAnimation = nullptr;
        }
        break;

    case State::Jumping:
        m_updateAnimation = m_sprite.startAnimation(FRAME_DURATION, {
            "hero_jump_0.png",
            "hero_jump_1.png"
        });
        break;

    case State::Walking:
        m_updateAnimation = m_sprite.startCyclicAnimation(FRAME_DURATION, {
            "hero_walk_0.png",
            "hero_walk_1.png",
            "hero_walk_2.png",
            "hero_walk_3.png",
            "hero_walk_4.png",
            "hero_walk_5.png"
        });
        break;
    }

    // Меняем состояние
    m_state = state;
}

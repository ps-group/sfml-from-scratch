#pragma once
#include "AnimatedSprite.h"
#include <SFML/Graphics.hpp>

class HeroPuppeteer
{
public:
	HeroPuppeteer(AnimatedSprite& sprite);

	// Экземпляры класса нельзя копировать
	HeroPuppeteer(const HeroPuppeteer&) = delete;
	HeroPuppeteer& operator=(const HeroPuppeteer&) = delete;

	void update(float dt);

private:
	enum class State
	{
		NotStarted,
		Idle,
		Walking,
		Jumping,
	};

	void updateIdleOrWalking(float dt);
	void updateJumping(float dt);
	void switchState(State state);

	AnimatedSprite& m_sprite;

	State m_state = State::NotStarted;
	sf::Vector2f m_speed;
	float m_jumpStartY = 0;
	AnimationUpdateFn m_updateAnimation;
};

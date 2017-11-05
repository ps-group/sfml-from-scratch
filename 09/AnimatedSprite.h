#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

// Тип данных: функция, выполняющая анимацию.
// @param dt - число секунд, прошедших с предыдущего кадра.
using AnimationUpdateFn = std::function<void(float dt)>;

// Класс AnimatedSprite имитирует sf::Sprite, но поддерживает покадровую анимацию.
// Для загрузки кадров используется текстурный атлас: изображение + информация о его нарезке.
// Атлас имеет формат, который соответствует формату Cheetah Texture Packer.
class AnimatedSprite
	: public sf::Drawable
	, public sf::Transformable
{
public:
	AnimatedSprite() = default;

	// Экземпляры класса нельзя копировать
	AnimatedSprite(const AnimatedSprite&) = delete;
	AnimatedSprite& operator=(const AnimatedSprite&) = delete;

	// Запускает нецикличную анимацию. Возвращает функцию, которая обновляет эту анимацию.
	// Возвращённую функцию нельзя использовать после разрушения спрайта.
	AnimationUpdateFn startAnimation(float frameDuration, const std::vector<std::string>& frames);

	// Запускает цикличную анимацию. Возвращает функцию, которая обновляет эту анимацию.
	// Возвращённую функцию нельзя использовать после разрушения спрайта.
	AnimationUpdateFn startCyclicAnimation(float frameDuration, const std::vector<std::string>& frames);

	// Возвращает текущий кадр анимации, отображаемый в спрайте.
	unsigned getCurrentFrame() const;

	// Выбирает кадр анимации по индексу в массиве кадров.
	// Возвращает true, если кадр с таким индексом существует.
	bool selectFrame(unsigned frameIndex);

	// Выбирает кадр анимации по имени исходного изображения.
	// Возвращает true, если кадр с таким именем существует.
	bool selectFrame(const std::string& name);

	// Загружает анимированный спрайт из двух файлов (изображение и *.atlas)
	bool loadFromFiles(const std::string& imagePath, const std::string& atlasPath);

protected:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
	struct SpriteFrame
	{
		std::string name;
		sf::IntRect rect;
	};

	static std::vector<SpriteFrame> loadAtlas(const std::string& filepath);
	void updateSprite();

	sf::Sprite m_sprite;
	sf::Texture m_texture;

	unsigned m_currentFrame = 0;
	std::vector<SpriteFrame> m_frames;
};

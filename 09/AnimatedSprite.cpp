#include "AnimatedSprite.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

// Загружает файл в строку.
//  NOTE: функция не сможет корректно обработать Unicode-пути на Windows
static std::string loadFileToUtf8String(const std::string& filepath)
{
    std::ifstream input(filepath);
    if (!input.is_open())
    {
        throw std::runtime_error("cannot open file " + filepath);
    }

    input.exceptions(std::ifstream::badbit);
    std::string content(
        (std::istreambuf_iterator<char>(input)),
        std::istreambuf_iterator<char>());

    return content;
}

// Разделяет строку на массив строк, используя указанный ASCII-символ как разделитель.
static std::vector<std::string> split(const std::string& content, char separator)
{
	std::vector<std::string> lines;
	std::string nextLine;
	for (char ch : content)
	{
		if (ch == separator)
		{
			lines.push_back(nextLine);
			nextLine.clear();
		}
		else
		{
			nextLine += ch;
		}
	}
	if (!nextLine.empty())
	{
		lines.push_back(nextLine);
	}
	return lines;
}

AnimationUpdateFn AnimatedSprite::startAnimation(float frameDuration, const std::vector<std::string>& frames)
{
	size_t index = 0;
	float frameTimeLeft = frameDuration;
	selectFrame(frames.at(index));

	return [=](float dt) mutable {
		frameTimeLeft -= dt;

		// Проверяем, что время кадра истекло и ещё есть кадры.
		// Используем цикл вместо if, потому что dt может быть больше длительности кадра.
		while ((frameTimeLeft < 0) && (index + 1 < frames.size()))
		{
			// Увеличиваем индекс.
			index += 1;
			selectFrame(frames.at(index));
			frameTimeLeft += frameDuration;
		}
	};
}

AnimationUpdateFn AnimatedSprite::startCyclicAnimation(float frameDuration, const std::vector<std::string>& frames)
{
	size_t index = 0;
	float frameTimeLeft = frameDuration;
	selectFrame(frames.at(index));

	return [=](float dt) mutable {
		frameTimeLeft -= dt;

		// Проверяем, что время кадра истекло.
		// Используем цикл вместо if, потому что dt может быть больше длительности кадра.
		while ((frameTimeLeft < 0))
		{
			// Увеличиваем индекс и делим по модулю на число кадров.
			index = (index + 1) % frames.size();
			selectFrame(frames.at(index));
			frameTimeLeft += frameDuration;
		}
	};
}

// Возвращает текущий кадр анимации, отображаемый в спрайте.
unsigned AnimatedSprite::getCurrentFrame() const
{
	return m_currentFrame;
}

bool AnimatedSprite::selectFrame(unsigned frameIndex)
{
	// Проверяем, нет ли выхода за границы массива.
	if (frameIndex < unsigned(m_frames.size()))
	{
		// Обновляем спрайт только если кадр изменился.
		if (m_currentFrame != frameIndex)
		{
			m_currentFrame = frameIndex;
			updateSprite();
		}
		return true;
	}
	return false;
}

bool AnimatedSprite::selectFrame(const std::string& name)
{
	// Ищем в массиве кадр с заданным именем.
	auto it = std::find_if(m_frames.begin(), m_frames.end(), [&](auto&& frame) {
		return frame.name == name;
	});

	// Вычисляем индекс кадра и выбираем по индексу.
	// Если кадр не найден, то it указывает за последний элемент массива,
	//  std::distance() вернёт размер массива, и тогда selectFrame вернёт false.
	return selectFrame(unsigned(std::distance(m_frames.begin(), it)));
}

bool AnimatedSprite::loadFromFiles(const std::string& imagePath, const std::string& atlasPath)
{
	std::vector<SpriteFrame> frames;

	// Пытаемся загрузить атлас. Если не получается, выводим описание ошибки и возвращаем false.
	try
	{
		frames = loadAtlas(atlasPath);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "cannot load atlas from '" << atlasPath << "', error: " << ex.what() << std::endl;
		return false;
	}

	// Пытаемся загрузить текстуру. Если не получается, возвращаем false.
	if (!m_texture.loadFromFile(imagePath))
	{
		return false;
	}

	// Обновляем состояние класса.
	m_frames = std::move(frames);
	m_sprite.setTexture(m_texture);
	updateSprite();

	return true;
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Применяем к render states трансформацию текущего объекта.
    states.transform.combine(getTransform());
    target.draw(m_sprite, states);
}

std::vector<AnimatedSprite::SpriteFrame> AnimatedSprite::loadAtlas(const std::string& filepath)
{
	const std::string content = loadFileToUtf8String(filepath);
	
	// Разделяем на строки и удаляем первую строку - комментарий вида "textures: man_hero.png"
	std::vector<std::string> lines = split(content, '\n');
	lines.erase(lines.begin());

	// Удаляем все пустые строки.
	auto newEnd = std::remove(lines.begin(), lines.end(), std::string());
	lines.erase(newEnd, lines.end());

	// Все оставшиеся строки выглядят так: "hero_walk_3.png	2	2	18	46	4	0	26	46	"
	// Каждую строку мы превращаем в SpriteFrame, хранящий имя состояния и координаты области текстуры.
	std::vector<SpriteFrame> frames;
	frames.reserve(lines.size());
	for (const std::string& line : lines)
	{
		const std::vector<std::string> words = split(line, '\t');
		const std::string& name = words.at(0);
		const int x = std::stoi(words.at(1));
		const int y = std::stoi(words.at(2));
		const int width = std::stoi(words.at(3));
		const int height = std::stoi(words.at(4));
		frames.push_back(SpriteFrame{name, sf::IntRect(x, y, width, height)});
	}
	return frames;
}

void AnimatedSprite::updateSprite()
{
	const sf::IntRect rect = m_frames.at(m_currentFrame).rect;

	std::cout << "switch to " << m_frames.at(m_currentFrame).name << std::endl;
	m_sprite.setTextureRect(rect);
	m_sprite.setOrigin(0.5f * sf::Vector2f{ float(rect.width), float(rect.height) });
}

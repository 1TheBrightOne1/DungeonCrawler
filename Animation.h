#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Globals.h"

class Animation
{
public:
	Animation() = default;
	Animation(sf::Texture animationSheet, sf::Vector2i spriteSize, unsigned int maxFrames, sf::Int32 threshold, bool interruptable, bool repeatable, unsigned int xOffset);
	~Animation();
	const sf::Texture& GetTexture();
	sf::IntRect GetActiveFrame(const sf::Time& elapsedTime);
	void Restart() { m_activeFrame = 0; m_finished = false; }
	bool IsInterruptable() { return m_interruptable || m_finished; }
	bool IsFinished() { return m_finished && !m_repeatable; }
private:
	sf::Texture m_animationSheet;
	sf::Vector2i m_frameSize;
	unsigned int m_activeFrame = 0;
	unsigned int m_maxFrames;
	sf::Int32 m_threshold;
	sf::Int32 m_current = 0;
	unsigned int m_xOffset;
	bool m_interruptable;
	bool m_finished = false;
	bool m_repeatable = true;
};
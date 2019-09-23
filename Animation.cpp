#include "Animation.h"

Animation::Animation(sf::Texture animationSheet, sf::Vector2i spriteSize, unsigned int maxFrames, sf::Int32 threshold, bool interruptable, bool repeatable, unsigned int xOffset) :
	m_animationSheet(std::move(animationSheet)), m_frameSize(std::move(spriteSize)), m_threshold(std::move(threshold)), m_maxFrames(maxFrames), m_xOffset(xOffset), m_interruptable(interruptable), m_repeatable(repeatable)
{
}

Animation::~Animation()
{
}

const sf::Texture& Animation::GetTexture()
{
	return m_animationSheet;
}

sf::IntRect Animation::GetActiveFrame(const sf::Time & elapsedTime)
{
	m_current += elapsedTime.asMilliseconds();
	if (m_current >= m_threshold)
	{
		++m_activeFrame;
		if (m_activeFrame >= m_maxFrames)
		{
			if (m_repeatable)
				m_activeFrame = 0;
			else
				m_activeFrame = m_maxFrames;
			m_finished = true;
		}
		m_current = 0;
	}
	return sf::IntRect(((m_xOffset + m_activeFrame * m_frameSize.x) % m_animationSheet.getSize().x), ((m_xOffset + m_activeFrame * m_frameSize.x) / m_animationSheet.getSize().x) * m_frameSize.y, m_frameSize.x, m_frameSize.y);
}

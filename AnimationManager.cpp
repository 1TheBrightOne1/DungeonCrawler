#include "AnimationManager.h"

void AnimationManager::AddAnimation(int state, AnimationManager::Builder& builder)
{
	m_animations[state] = builder.Build();
}

void AnimationManager::SetActiveAnimation(int state)
{
	m_animations[m_activeAnimation].Restart();
	m_activeAnimation = state;
}

void AnimationManager::GetActiveFrame(const sf::Time & elapsedTime, sf::Sprite& sprite)
{
	sprite.setTexture(m_animations[m_activeAnimation].GetTexture());
	sf::IntRect newFrame = m_animations[m_activeAnimation].GetActiveFrame(elapsedTime);
	if (m_flipAnimation)
	{
		newFrame.left += newFrame.width;
		newFrame.width *= -1;
	}
	sprite.setTextureRect(newFrame);
}

bool AnimationManager::AnimationFinished()
{
	return m_animations[m_activeAnimation].IsFinished();
}

AnimationManager::Builder::Builder(sf::Texture animationSheet, unsigned int totalFrames, sf::Int32 threshold) :
	m_animationSheet(animationSheet), m_totalFrames(totalFrames), m_threshold(threshold)
{
}

AnimationManager::Builder & AnimationManager::Builder::SetInterruptable(bool val)
{
	m_interruptable = val;
	return *this;
}

AnimationManager::Builder & AnimationManager::Builder::SetRepeat(bool val)
{
	m_repeatable = val;
	return *this;
}

AnimationManager::Builder & AnimationManager::Builder::SetOriginOffset(unsigned int xOffset)
{
	m_xOriginOffset = xOffset;
	return *this;
}

AnimationManager::Builder & AnimationManager::Builder::SetFrameSize(sf::Vector2i frameSize)
{
	m_frameSize = frameSize;
	return *this;
}

Animation AnimationManager::Builder::Build()
{
	return Animation{ m_animationSheet, m_frameSize, m_totalFrames, m_threshold, m_interruptable, m_repeatable, m_xOriginOffset };
}
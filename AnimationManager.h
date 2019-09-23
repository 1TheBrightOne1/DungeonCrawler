#pragma once

#include <map>
#include <deque>
#include "Animation.h"

class AnimationManager
{
	std::map<int, Animation> m_animations;
	int m_activeAnimation;
	bool m_flipAnimation = false;
	std::deque<int> m_animationQueue;
public:
	class Builder
	{
		sf::Texture m_animationSheet;
		unsigned int m_totalFrames;
		bool m_interruptable = true;
		bool m_repeatable = true;
		sf::Int32 m_threshold;
		unsigned int m_xOriginOffset = 0; //Used when the first frame doesn't start immediately on the texture given
		sf::Vector2i m_frameSize = sf::Vector2i(TILE_SIZE, TILE_SIZE);
	public:
		Builder(sf::Texture animationSheet, unsigned int totalFrames, sf::Int32 threshold);
		Builder& SetInterruptable(bool val);
		Builder& SetRepeat(bool val);
		Builder& SetOriginOffset(unsigned int xOffset);
		Builder& SetFrameSize(sf::Vector2i frameSize);
		Animation Build();
	};
	void AddAnimation(int state, AnimationManager::Builder& builder);
	void SetActiveAnimation(int state);
	void GetActiveFrame(const sf::Time& elapsedTime, sf::Sprite& sprite);
	bool AnimationFinished();
	void SetFlipped(bool val) { m_flipAnimation = val; }
	int Count() { return m_animations.size(); }
};
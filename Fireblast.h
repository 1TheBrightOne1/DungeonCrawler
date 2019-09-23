#pragma once
#include <memory>
#include "CircularTarget.h"
#include "AnimationManager.h"

class Fireblast :
	public CircularTarget
{
	AnimationManager animation;
public:
	Fireblast(int parent);
	~Fireblast();
	bool Do(const sf::Time& elapsedTime);
	void ShowPlus(const sf::Time& elapsedTime);
};
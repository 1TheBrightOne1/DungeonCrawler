#pragma once
#include "TargetedAction.h"
#include "AnimationManager.h"
#include "DynamicEntity.h"

class MagicMissile :
	public TargetedAction
{
	AnimationManager animation;
public:
	MagicMissile(int parent);
	~MagicMissile();

	bool Do(const sf::Time& elapsedTime);
	bool Show(const sf::Time& elapsedTime);
};

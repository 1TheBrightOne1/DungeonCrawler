#pragma once

#include "DynamicEntity.h"
#include "TargetedAction.h"

class Projectile : public DynamicEntity, public TargetedAction
{
public:
	Projectile(int parent, const DynamicEntityArgs& args);
	~Projectile();

	//bool Do(const sf::Time& elapsedTime);
	bool Show(const sf::Time& elapsedTime);
};


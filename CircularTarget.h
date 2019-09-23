#pragma once
#include "TargetedAction.h"
class CircularTarget :
	public TargetedAction
{
protected:
	int maxDistance = 50;
	int radius = 2 * TILE_SIZE;

	std::vector<int> GetAffectedEntities();
public:
	CircularTarget(int parent);
	~CircularTarget();
	bool Show(const sf::Time& elapsedTime);
};


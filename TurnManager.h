#pragma once

#include <vector>
#include "DynamicEntity.h"

class TurnManager
{
	std::vector<std::weak_ptr<DynamicEntity>> turnOrder;
	int turnIndex;
public:
	TurnManager();
	~TurnManager();
	void Add(std::weak_ptr<DynamicEntity> newCharacter);
	void Update(const sf::Time& elapsedTime);
};


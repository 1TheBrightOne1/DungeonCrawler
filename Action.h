#pragma once

#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "EventManager.h"
#include <string>
#include <vector>

class Action
{
protected:
	int parentEntity;
	int pointsNeeded;
	std::vector<std::shared_ptr<Observer>> observers;
public:
	Action(int parent) { parentEntity = parent; }
	~Action();
	int GetCost() { return pointsNeeded; }
	virtual bool Show(const sf::Time& elapsedTime) { return true; }
	virtual bool Do(const sf::Time& elapsedTime) = 0;
};
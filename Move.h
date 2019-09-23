#pragma once

#include <functional>
#include <vector>
#include "Action.h"
#include "Pathfinder.h"
#include "Kinematics.h"

class Move :
	public Action
{
	sf::Vector2f destination;
	std::vector<sf::Vector2f> moves;
	int movesAllowed;
public:
	Move(int entityID, int movesAllowed);
	~Move();
	bool Do(const sf::Time& elapsedTime);
	bool Show(const sf::Time& elapsedTime);
	sf::Vector2f CalcVelocity(const sf::Vector2f& oldPosition, sf::Vector2f newPosition);
};

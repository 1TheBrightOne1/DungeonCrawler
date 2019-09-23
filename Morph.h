#pragma once
#include "Action.h"
#include "SpriteManager.h"
class Morph :
	public Action
{
public:
	Morph(int entityID);
	~Morph();
	bool Do(const sf::Time& elapsedTime);
};
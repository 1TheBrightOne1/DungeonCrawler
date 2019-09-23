#pragma once
#include "StaticEntity.h"
class Floor :
	public StaticEntity
{
public:
	Floor(const sf::Vector2f& position);
	~Floor();
};
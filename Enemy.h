#pragma once
#include "DynamicEntity.h"
class Enemy :
	public DynamicEntity
{
public:
	Enemy(const sf::Vector2f& position);
	~Enemy();
	void InitAnimations();
};


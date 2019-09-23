#pragma once
#include <cstdlib>
#include <vector>
#include "SFML/Graphics.hpp"
#include "DynamicEntity.h"
#include "Button.h"
#include "MagicMissile.h"

class Player : public DynamicEntity
{
	std::vector<InterfaceMetadata> interface;
	void InitAnimations();
public:
	Player(const sf::Vector2f& position);
	~Player();
};


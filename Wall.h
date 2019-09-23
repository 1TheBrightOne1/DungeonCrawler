#pragma once

#include "SFML/Graphics.hpp"
#include "StaticEntity.h"

class Wall : public StaticEntity
{
public:
	Wall(const sf::Vector2f& position);
	~Wall();
};
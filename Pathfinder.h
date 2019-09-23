#pragma once
#include <map>
#include "SFML/Graphics.hpp"
#include "CollisionManager.h"
#include "SpriteManager.h"
#include "Entity.h"

typedef std::pair<int, int> Grid;

struct Tile
{
	Grid location;
	Grid parent;
	int g;
	int h;
};

std::vector<sf::Vector2f> GetPath(int entityID, sf::Vector2f start, sf::Vector2f finish, bool getClosest = false);
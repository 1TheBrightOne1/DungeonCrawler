#pragma once
#include <string>
#include <memory>
#include <functional>
#include "SFML/Graphics.hpp"
#include "CollisionManager.h"
#include "SpriteManager.h"
#include "Globals.h"

class Entity
{
protected:
	int entityID;
	static int counter;
public:
	Entity(const std::string& fileName, const sf::IntRect& subTexture);
	~Entity();
	virtual void OnCollision(int direction) {}
	virtual sf::IntRect GetPosition() = 0;
	int GetEntityID() { return entityID; }
};


#pragma once
#include <string>
#include "Entity.h"
#include "Background.h"

class StaticEntity : public Entity
{
protected:
	sf::IntRect position;
public:
	StaticEntity(const std::string& fileName, const sf::IntRect& subTexture, const sf::Vector2f& position, bool hasCollision, const std::string& key = "background");
	~StaticEntity();
	sf::IntRect GetPosition() { return position; }
};
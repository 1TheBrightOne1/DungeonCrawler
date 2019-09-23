#include "Entity.h"

int Entity::counter = 0;


Entity::Entity(const std::string& fileName, const sf::IntRect& subTexture)
{
	entityID = ++counter;
}


Entity::~Entity()	
{
}

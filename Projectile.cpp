#include "Projectile.h"



Projectile::Projectile(int entity, const DynamicEntityArgs& args) :
	DynamicEntity(args),
	TargetedAction(entity)
{
}

Projectile::~Projectile()
{
}

bool Projectile::Show(const sf::Time& elapsedTime)
{
	auto parentLocation = SpriteManager::GetSprite(parentEntity)->sprite->getPosition();
	auto mouseLocation = sf::Vector2f(sf::Mouse::getPosition(window));
	return true;
	//float angle = 
}

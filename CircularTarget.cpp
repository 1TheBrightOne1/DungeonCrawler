#include "CircularTarget.h"


std::vector<int> CircularTarget::GetAffectedEntities()
{
	std::vector<int> entities;

	for (const auto& sprite : SpriteManager::GetSprites())
	{
		if (sprite.second.expired())
			continue;

		sf::Vector2f position = sprite.second.lock()->sprite->getPosition();
		position -= target;
		position.x *= position.x;
		position.y *= position.y;

		if (position.x + position.y - radius * radius <= 0)
		{
			entities.push_back(sprite.first);
		}
	}

	return entities;
}

CircularTarget::CircularTarget(int parent) : TargetedAction(parent)
{
	
}

CircularTarget::~CircularTarget()
{
}

bool CircularTarget::Show(const sf::Time& elapsedTime)
{
	if (target != sf::Vector2f())
	{
		preview.reset();
		return true;
	}

	auto sprite = SpriteManager::GetSprite(parentEntity)->sprite;
	auto spritePosition = sprite->getPosition();
	spritePosition.x += sprite->getTextureRect().width / 2;
	spritePosition.y += sprite->getTextureRect().height / 2;
	auto newTarget = sf::Vector2f(sf::Mouse::getPosition(window));
	float yChange = newTarget.y - spritePosition.y;
	float xChange = newTarget.x - spritePosition.x;
	float distance = sqrt(yChange * yChange + xChange * xChange);
	if (distance > maxDistance)
	{
		float angle = atan(abs(yChange) / abs(xChange));
		float adjustedy = sin(angle) * maxDistance;
		float adjustedx = cos(angle) * maxDistance;
		if (yChange < 0)
			adjustedy *= -1;
		if (xChange < 0)
			adjustedx *= -1;
		newTarget.x = spritePosition.x + adjustedx;
		newTarget.y = spritePosition.y + adjustedy;
	}
	
	preview->sprite->setPosition(static_cast<sf::Vector2f>(newTarget));
	ShowPlus(elapsedTime);
	return false;
}

#include "CollisionManager.h"

std::map<int, CollisionManager::CollisionEntity> CollisionManager::entities = std::map<int, CollisionEntity>();

bool CollisionManager::Collided(const sf::IntRect & a, const sf::IntRect & b)
{
	if (a.left >= b.left + b.width || a.left + a.width <= b.left ||
		a.top >= b.top + b.height || a.top + a.height <= b.top)
		return false;
	std::cout << "Collision\n";
	return true;
}

void CollisionManager::Update()
{
	for (int i = 0; i < entities.size(); ++i)
	{
		if (CheckCollision(i))
			entities[i].callback(1);
	}
}

bool CollisionManager::CheckCollision(int id)
{
	sf::IntRect a = entities[id].getPosition();
	
	for (const auto & entity : entities)
	{
		sf::IntRect b = entity.second.getPosition();
		if (entity.first != id && Collided(a, b))
			return true;
	}
	return false;
}

bool CollisionManager::IsOccupied(int excludedId, const sf::IntRect & location)
{
	for (const auto& entity : entities)
	{
		if (entity.first != excludedId)
		{
			if (Collided(entity.second.getPosition(), location))
				return true;
		}
	}
	return false;
}

void CollisionManager::Subscribe(int entityID, std::function<sf::IntRect(void)> getPosition, std::function<void(int)> callback)
{
	entities[entityID] = CollisionEntity(getPosition, callback);
}

void CollisionManager::Unsubscribe(int entityID)
{
	entities.erase(entityID);
}

int CollisionManager::GetCollidedEntity(sf::Vector2f location)
{
	sf::IntRect tile = sf::IntRect(location.x, location.y, TILE_SIZE, TILE_SIZE);
	for (const auto& entity : entities)
	{
		if (Collided(tile, entity.second.getPosition()))
			return entity.first;
	}
	return -1;
}

CollisionManager::CollisionEntity::CollisionEntity(std::function<sf::IntRect(void)> getPosition, std::function<void(int)> callback) :
	getPosition(getPosition), callback(callback)
{
}

CollisionManager::CollisionEntity::~CollisionEntity()
{
}

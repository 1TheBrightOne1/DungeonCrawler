#include "StaticEntity.h"

StaticEntity::StaticEntity(const std::string & fileName, const sf::IntRect & subTexture, const sf::Vector2f & position, bool hasCollision, const std::string& key) : Entity(fileName, subTexture)
{
	if (hasCollision)
	{
		auto getPosition = std::bind(&Entity::GetPosition, this);
		auto callback = std::bind(&Entity::OnCollision, this, std::placeholders::_1);
		CollisionManager::Subscribe(GetEntityID(), getPosition, callback);
	}

	this->position.left = position.x;
	this->position.top = position.y;
	this->position.width = subTexture.width;
	this->position.height = subTexture.height;

	sf::Vertex quad[4];
	quad[0].position = position;
	quad[1].position = position;
	quad[1].position.x += subTexture.width;
	quad[2].position = position;
	quad[2].position.x += subTexture.width;
	quad[2].position.y += subTexture.height;
	quad[3].position = position;
	quad[3].position.y += subTexture.height;

	quad[0].texCoords = sf::Vector2f(subTexture.left, subTexture.top);
	quad[1].texCoords = sf::Vector2f(subTexture.left + subTexture.width, subTexture.top);
	quad[2].texCoords = sf::Vector2f(subTexture.left + subTexture.width, subTexture.top + subTexture.height);
	quad[3].texCoords = sf::Vector2f(subTexture.left, subTexture.top + subTexture.height);

	for (auto x : quad)
		Background::AppendVertex(fileName, x, key);
}

StaticEntity::~StaticEntity()
{
}

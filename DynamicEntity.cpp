#include "DynamicEntity.h"

void DynamicEntity::Init(const std::string & fileName, const sf::IntRect & subTexture, const sf::Vector2f & position)
{
	sprite = SpriteManager::CreateSprite(GetEntityID(), fileName, subTexture);
	sprite->sprite->setPosition(position);

	auto getPosition = std::bind(&Entity::GetPosition, this);
	auto callback = std::bind(&Entity::OnCollision, this, std::placeholders::_1);
	CollisionManager::Subscribe(GetEntityID(), getPosition, callback);

	newPosition = position;

	kinematics = KinematicsManager::Subscribe(GetEntityID(), position, sf::Vector2f(0, 0));

	stats = CombatManager::Subscribe(GetEntityID(), 1);
}

DynamicEntity::DynamicEntity(const std::string & fileName, const sf::IntRect & subTexture, const sf::Vector2f& position) : Entity(fileName, subTexture)
{
	Init(fileName, subTexture, position);
}

DynamicEntity::DynamicEntity(const DynamicEntityArgs & args) : Entity(args.fileName, args.subTexture)
{
	Init(args.fileName, args.subTexture, args.position);
}

DynamicEntity::~DynamicEntity()
{
	SpriteManager::RemoveSprite(this->entityID);
	CollisionManager::Unsubscribe(this->entityID);
	KinematicsManager::Unsubscribe(this->entityID);
}

sf::IntRect DynamicEntity::GetPosition()
{
	sf::IntRect entity;
	sf::Vector2f position = sprite->sprite->getPosition();
	entity.left = position.x;
	entity.top = position.y;

	sf::IntRect size = sprite->sprite->getTextureRect();
	entity.width = size.width;
	entity.height = size.height;
	return entity;
}

void DynamicEntity::Update(const sf::Time & elapsedTime)
{
	if (activeAction == nullptr && actions.size() > 0)
	{
		if (actions.front()->Show(elapsedTime))
		{
			if (actions.front()->GetCost() > this->pointsAvailable)
			{
				actions.pop();
			}
			else
			{
				activeAction = actions.front();
				actions.pop();
			}
		}
	}
	if (activeAction != nullptr)
	{
		if (activeAction->Do(elapsedTime))
		{
			pointsAvailable -= activeAction->GetCost();
			activeAction.reset();
		}
	}
	if (kinematics->GetVelocity().x < 0)
		m_animations.SetFlipped(true);
	else if (kinematics->GetVelocity().x > 0)
		m_animations.SetFlipped(false);
	m_animations.GetActiveFrame(elapsedTime, *sprite->sprite);
	
	sprite->sprite->setPosition(kinematics->GetPosition());
}

bool DynamicEntity::Idle()
{
	return pointsAvailable == 0;
}

bool DynamicEntity::Remove()
{
	if (stats->GetHP() <= 0)
		return true;
	return false;
}

void DynamicEntity::OnCollision(int direction)
{
	kinematics->SetVelocity(sf::Vector2f(0, 0));
}
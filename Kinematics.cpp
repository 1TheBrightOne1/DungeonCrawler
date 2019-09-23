#include "Kinematics.h"

std::map<int, std::weak_ptr<Kinematics>> KinematicsManager::entities = std::map<int, std::weak_ptr<Kinematics>>();

Kinematics::Kinematics(const sf::Vector2f & initialPosition, const sf::Vector2f & initialVelocity) :
	position(initialPosition), velocity(initialVelocity)
{
}

Kinematics::~Kinematics()
{
}

const sf::Vector2f Kinematics::GetPosition()
{
	return position;
}

const sf::Vector2f Kinematics::GetVelocity()
{
	return velocity;
}

void Kinematics::SetVelocity(const sf::Vector2f & newVelocity)
{
	velocity = newVelocity;
}

void Kinematics::SetPosition(const sf::Vector2f & newPosition)
{
	position = newPosition;
}

void Kinematics::Update(const sf::Time & elapsedTime)
{
	position.x += velocity.x * elapsedTime.asMilliseconds() / 1000;
	position.y += velocity.y * elapsedTime.asMilliseconds() / 1000;
}

std::shared_ptr<Kinematics> KinematicsManager::Subscribe(int entity, const sf::Vector2f & initialPosition, const sf::Vector2f & initialVelocity)
{
	auto sp = std::make_shared<Kinematics>(initialPosition, initialVelocity);
	entities[entity] = sp;
	return sp;
}

void KinematicsManager::Unsubscribe(int entity)
{
	entities.erase(entity);
}

void KinematicsManager::Update(const sf::Time & elapsedTime)
{
	for (auto& x : entities)
	{
		x.second.lock()->Update(elapsedTime);
	}
}

#pragma once

#include <map>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Entity.h"

class KinematicsManager;

class Kinematics
{
	friend KinematicsManager;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float baseSpeed = 5.0f;
public:
	Kinematics(const sf::Vector2f& initialPosition, const sf::Vector2f& initialVelocity);
	~Kinematics();
	const sf::Vector2f GetPosition();
	const sf::Vector2f GetVelocity();
	float GetBaseSpeed() { return baseSpeed; }
	void SetVelocity(const sf::Vector2f& newVelocity);
	void SetPosition(const sf::Vector2f& newPosition);
	void Update(const sf::Time& elapsedTime);
};

class KinematicsManager
{
	static std::map<int, std::weak_ptr<Kinematics>> entities;
public:
	static std::shared_ptr<Kinematics> Subscribe(int entity, const sf::Vector2f& initialPosition, const sf::Vector2f& initialVelocity);
	static void Unsubscribe(int entity);
	static Kinematics* GetKinematics(int entity) { return &(*entities[entity].lock()); }
	static void Update(const sf::Time& elapsedTime);
};
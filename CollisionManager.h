#pragma once
#include <vector>
#include <functional>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Globals.h"

class CollisionManager
{
	struct CollisionEntity
	{
		bool hasMoved;
		std::function<sf::IntRect(void)> getPosition;
		std::function<void(int)> callback;

		CollisionEntity(std::function<sf::IntRect(void)> getPosition, std::function<void(int)> callback);
		CollisionEntity() = default;
		~CollisionEntity();
	};

	static std::map<int, CollisionEntity> entities;
	static bool Collided(const sf::IntRect& a, const sf::IntRect& b);
public:
	static void Update();
	static void Subscribe(int entityID, std::function<sf::IntRect(void)> getPosition, std::function<void(int)> callback);
	static void Unsubscribe(int entityID);
	static int GetCollidedEntity(sf::Vector2f location);
	static bool CheckCollision(int id);
	static bool IsOccupied(int excludedId, const sf::IntRect& location);
};


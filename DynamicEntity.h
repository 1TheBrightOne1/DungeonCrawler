#pragma once

#include "Entity.h"
#include "Kinematics.h"
#include "Move.h"
#include "Fireblast.h"
#include "CombatStats.h"
#include "Layout.h"
#include "AnimationManager.h"
#include <queue>

struct DynamicEntityArgs
{
	std::string fileName;
	sf::IntRect subTexture;
	sf::Vector2f position;
	DynamicEntityArgs(const std::string& fileName, const sf::IntRect& subTexture, const sf::Vector2f& position):
		fileName(fileName),
		subTexture(subTexture),
		position(position)
	{}
};

class DynamicEntity : public Entity
{
protected:
	std::shared_ptr<SpriteResource> sprite;
	std::shared_ptr<Kinematics> kinematics;
	std::queue<std::shared_ptr<Action>> actions;
	std::shared_ptr<Action> activeAction;
	std::shared_ptr<CombatStats> stats;
	AnimationManager m_animations;

	int actionPoints = 1600;
	int pointsAvailable;
	void OnCollision(int direction);

	sf::Vector2f newPosition;

	void Init(const std::string& fileName, const sf::IntRect& subTexture, const sf::Vector2f& position);
	
public:
	DynamicEntity(const std::string& fileName, const sf::IntRect& subTexture, const sf::Vector2f& position);
	DynamicEntity(const DynamicEntityArgs& args);
	~DynamicEntity();
	sf::IntRect GetPosition();
	void Update(const sf::Time& elapsedTime);
	void ResetPoints() { pointsAvailable = actionPoints;}
	void AddAction(std::shared_ptr<Action> action) { actions.push(action); }
	bool Idle();
	bool Remove();
};
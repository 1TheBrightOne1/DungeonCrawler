#pragma once
#include "Action.h"
#include "SpriteManager.h"
#include "CollisionManager.h"
#include "CombatStats.h"

class TargetedAction :
	public Action
{
protected:
	int damage = 1;
	std::shared_ptr<SpriteResource> preview;
	sf::Vector2f target;
	void SetTarget(const sf::Vector2f& target) { this->target = target; }
	virtual std::vector<int> GetAffectedEntities() { return {}; };
	void HitEntities();
	virtual void ShowPlus(const sf::Time& elapsedTime) {}
public:
	TargetedAction(int parent);
	~TargetedAction();
};
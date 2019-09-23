#include "TargetedAction.h"


void TargetedAction::HitEntities()
{
	auto tiles = GetAffectedEntities();
	for (const auto& x : tiles)
	{
		/*
		int collidedEntity = CollisionManager::GetCollidedEntity(x);
		if (collidedEntity != -1)
		{
			auto entity = CombatManager::GetStats(collidedEntity);
			if (entity != nullptr)
			{
				entity->SetHP(entity->GetHP() - damage);
			}
		}*/
	}
}

TargetedAction::TargetedAction(int parent) : Action(parent)
{
	observers.push_back(EventManager::Subscribe(Click, [=](const sf::Event& event) {
		this->SetTarget(preview->sprite->getPosition());
	}));
}


TargetedAction::~TargetedAction()
{

}

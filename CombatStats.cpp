#include "CombatStats.h"

std::map<int, std::weak_ptr<CombatStats>> CombatManager::combatStats = std::map<int, std::weak_ptr<CombatStats>>();

CombatStats::~CombatStats()
{
}

std::shared_ptr<CombatStats> CombatManager::GetStats(int entityID)
{
	if (combatStats.find(entityID) == combatStats.end())
		return std::shared_ptr<CombatStats>();
	return combatStats[entityID].lock();
}

std::shared_ptr<CombatStats> CombatManager::Subscribe(int entityID, int health)
{
	auto sp = std::make_shared<CombatStats>(health);
	combatStats[entityID] = sp;
	return sp;
}

#pragma once

#include <map>
#include <memory>

class CombatStats
{
	int hp;
public:
	CombatStats(int hp) : hp(hp){}
	~CombatStats();

	int GetHP() { return hp; }
	void SetHP(int hp) { this->hp = hp; }
};

class CombatManager
{
	static std::map<int, std::weak_ptr<CombatStats>> combatStats;
public:
	static std::shared_ptr<CombatStats> GetStats(int entityID);
	static std::shared_ptr<CombatStats> Subscribe(int entityID, int health);
};
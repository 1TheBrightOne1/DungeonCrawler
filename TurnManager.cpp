#include "TurnManager.h"



TurnManager::TurnManager()
{
}


TurnManager::~TurnManager()
{
}

void TurnManager::Add(std::weak_ptr<DynamicEntity> newCharacter)
{
	turnOrder.push_back(newCharacter);
	if (turnOrder.size() == 1)
		turnOrder[0].lock()->ResetPoints();
}

void TurnManager::Update(const sf::Time& elapsedTime)
{
	auto validate = [&](size_t index) {
		if (turnOrder[turnIndex].expired())
		{
			turnOrder.erase(turnOrder.begin() + turnIndex);
			return false;
		}
		return true;
	};
	if (validate(turnIndex))
	{
		auto sp = turnOrder[turnIndex].lock();
		if (sp->Idle())
		{
			++turnIndex;
			if (turnIndex >= turnOrder.size())
				turnIndex = 0;
			while (!validate(turnIndex))
			{
				turnIndex = turnIndex >= turnOrder.size() ? 0 : ++turnIndex;
			}
			turnOrder[turnIndex].lock()->ResetPoints();
		}
	}

	std::vector<size_t> remove;
	for (size_t iii = 0; iii < turnOrder.size(); ++iii)
	{
		if (turnOrder[iii].expired())
			remove.push_back(iii);
		else
			turnOrder[iii].lock()->Update(elapsedTime);
	}
}

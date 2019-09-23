#include "Action.h"

Action::~Action()
{
	for (auto& x : observers)
	{
		EventManager::Unsubscribe(x);
	}
}

#include "EventManager.h"

std::map <EventType, std::vector<std::weak_ptr<Observer>>> EventManager::subscribers = std::map <EventType, std::vector<std::weak_ptr<Observer>>>();
std::vector<std::weak_ptr<Observer>> EventManager::newSubscribers = std::vector<std::weak_ptr<Observer>>();

int EventManager::id = 0;

void EventManager::Signal(EventType eventType, const sf::Event & event)
{
	for (int iii = 0; iii < subscribers[eventType].size(); ++iii)
	{
		if (!subscribers[eventType][iii].expired())
				subscribers[eventType][iii].lock()->callback(event);
	}
}

void EventManager::Handle(const sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Button::Left)
		{
			Signal(Click, event);
		}
	}

	if (newSubscribers.size() > 0)
	{
		for (auto& subscriber : newSubscribers)
		{
			subscribers[(subscriber.lock()->type)].push_back(subscriber);
		}
		newSubscribers.clear();
	}
}

std::shared_ptr<Observer> EventManager::Subscribe(EventType event, std::function<void(const sf::Event&)> callback)
{
	std::shared_ptr<Observer> sp = std::make_shared<Observer>(event, id, callback);
	++id;
	newSubscribers.push_back(sp);
	return sp;
}

void EventManager::Unsubscribe(std::shared_ptr<Observer> target)
{
	EventType type = target->type;

	for (int iii = subscribers[type].size() - 1; iii >= 0; --iii)
	{
		if (subscribers[type][iii].expired())
		{
			subscribers[type].erase(subscribers[type].begin() + iii - 1);
			continue;
		}
		if (subscribers[type][iii].lock()->id == target->id)
		{
			subscribers[type].erase(subscribers[type].begin() + iii);
			break;
		}
	}
}

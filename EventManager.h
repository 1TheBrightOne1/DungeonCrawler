#pragma once

#include <map>
#include <vector>
#include <functional>
#include <algorithm>
#include "SFML/Graphics.hpp"

enum EventType
{
	Click
};

struct Observer
{
	EventType type;
	int id;
	std::function<void(const sf::Event&)> callback;
	Observer(EventType type, int id, std::function<void(const sf::Event&)> callback) : type(type), id(id), callback(callback) {}
};

class EventManager
{
	static int id;
	static std::map <EventType, std::vector<std::weak_ptr<Observer>>> subscribers;
	static std::vector<std::weak_ptr<Observer>> newSubscribers;
	static void Signal(EventType eventType, const sf::Event& event);
public:
	static void Handle(const sf::Event& event);
	static std::shared_ptr<Observer> Subscribe(EventType event, std::function<void(const sf::Event&)> callback);
	static void Unsubscribe(std::shared_ptr<Observer> target);
};


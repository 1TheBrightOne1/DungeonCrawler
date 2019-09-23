#pragma once

#include "SFML/Graphics.hpp"
#include "SpriteManager.h"
#include "StaticEntity.h"
#include "EventManager.h"
#include <functional>
#include <string>

struct InterfaceMetadata
{
	std::string fileName;
	sf::IntRect textureLocation;
	std::string name;
	std::string tooltip;
	std::function<void(const sf::Event&)> callback;

	InterfaceMetadata(const std::string& fileName, const sf::IntRect& textureLocation, const std::string& name, const std::string& tooltip, const std::function<void(const sf::Event&)> callback);
};

class Button : StaticEntity
{
	InterfaceMetadata metadata;
	std::shared_ptr<Observer> observer;
public:
	Button(InterfaceMetadata metadata, const sf::Vector2f& position);
	~Button();
};
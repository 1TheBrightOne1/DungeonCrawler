#pragma once

#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Button.h"
#include "Background.h"

class Layout
{
	static sf::RectangleShape mapOutline;
	static sf::RectangleShape interfaceOutline;
	static sf::RectangleShape turnOrderOutline;
	static std::vector<Button> buttons;
public:
	Layout();
	~Layout();
	static const sf::RectangleShape GetMapBoundary() { return mapOutline; }
	static const sf::RectangleShape GetInterfaceBoundary() { return interfaceOutline; }
	static const sf::RectangleShape GetTurnOrderOutline() { return turnOrderOutline; }
	static void DrawLayout(sf::RenderWindow& window);
	static void SetInterface(const std::vector<InterfaceMetadata> buttons);
};


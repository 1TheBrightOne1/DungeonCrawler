#include "Layout.h"

sf::RectangleShape Layout::mapOutline(sf::Vector2f(30 * TILE_SIZE, 30 * TILE_SIZE));
sf::RectangleShape Layout::interfaceOutline(sf::Vector2f(30 * TILE_SIZE, 4 * TILE_SIZE));
sf::RectangleShape Layout::turnOrderOutline(sf::Vector2f(20 * TILE_SIZE, 4 * TILE_SIZE));
std::vector<Button> Layout::buttons = std::vector<Button>();

Layout::Layout() 
{
	auto initShape = [](sf::Shape& shape) {
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Blue);
		shape.setOrigin(0, 0);
		shape.setOutlineThickness(3);
	};

	initShape(mapOutline);
	initShape(interfaceOutline);
	initShape(turnOrderOutline);
	mapOutline.setPosition((SCREEN_HEIGHT - mapOutline.getSize().y) / 2, (SCREEN_WIDTH - mapOutline.getSize().x) / 2);
	auto alignX = mapOutline.getPosition().x;
	alignX -= static_cast<int>(alignX) % TILE_SIZE;
	auto alignY = mapOutline.getPosition().y;
	alignY -= static_cast<int>(alignY) % TILE_SIZE;
	mapOutline.setPosition(alignX, alignY);
	interfaceOutline.setPosition(sf::Vector2f(mapOutline.getPosition().x, mapOutline.getPosition().y + mapOutline.getSize().y));
	turnOrderOutline.setPosition(sf::Vector2f(mapOutline.getPosition().x + (mapOutline.getSize().x - turnOrderOutline.getSize().x) / 2, mapOutline.getPosition().y - turnOrderOutline.getSize().y - turnOrderOutline.getOutlineThickness()));
}

Layout::~Layout()
{
}

void Layout::DrawLayout(sf::RenderWindow & window)
{
	window.draw(mapOutline);
	window.draw(interfaceOutline);
	window.draw(turnOrderOutline);
}

void Layout::SetInterface(const std::vector<InterfaceMetadata> buttons)
{
	Layout::buttons.clear();
	int count = 0;
	for (auto& button : buttons)
	{
		Layout::buttons.emplace_back(button, sf::Vector2f(interfaceOutline.getPosition().x + count * 100, interfaceOutline.getPosition().y));
		++count;
	}
}

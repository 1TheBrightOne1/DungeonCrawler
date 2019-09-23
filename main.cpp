#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Player.h"
#include "Background.h"
#include "Wall.h"
#include "Floor.h"
#include "Enemy.h"
#include "TurnManager.h"
#include "Kinematics.h"
#include "Morph.h"
#include "Globals.h"
#include "Layout.h"

int main()
{
	std::vector<Wall> walls;
	std::vector<Floor> floor;

	TurnManager turnManager;

	std::vector<std::shared_ptr<DynamicEntity>> entities;
	Layout layout;
	walls.reserve(1000);

	std::string in;
	std::ifstream readFile("Maze.txt");
	int row = 0;
	while (!readFile.eof())
	{
		std::getline(readFile, in);
		int col = 0;
		for (auto& x : in)
		{
			if (x == 'P')
			{
				auto player = std::make_shared<Player>(sf::Vector2f(layout.GetMapBoundary().getPosition().x + col * TILE_SIZE, layout.GetMapBoundary().getPosition().y + row * TILE_SIZE));
				turnManager.Add(player);
				entities.push_back(player);
				//floor.emplace_back(sf::Vector2f(col * TILE_SIZE, row * TILE_SIZE));
			}
			else if (x == 'E')
			{
				auto enemy = std::make_shared<Enemy>(sf::Vector2f(layout.GetMapBoundary().getPosition().x + col * TILE_SIZE, layout.GetMapBoundary().getPosition().y + row * TILE_SIZE));
				turnManager.Add(enemy);
				entities.push_back(enemy);
				//floor.emplace_back(sf::Vector2f(col * TILE_SIZE, row * TILE_SIZE));
			}
			else if (x != ' ')
				walls.emplace_back(sf::Vector2f(layout.GetMapBoundary().getPosition().x + col * TILE_SIZE, layout.GetMapBoundary().getPosition().y + row * TILE_SIZE));
			//else
				//floor.emplace_back(sf::Vector2f(col * TILE_SIZE, row * TILE_SIZE));
			++col;
		}
		++row;
	}
	readFile.close();

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			EventManager::Handle(event);
		}

		for (auto it = entities.begin(); it != entities.end(); ++it)
		{
			if ((*it)->Remove())
			{
				it = entities.erase(it);
				--it;
			}
		}

		auto timeElapsed = clock.getElapsedTime();
		KinematicsManager::Update(timeElapsed);
		turnManager.Update(timeElapsed);
		if (clock.getElapsedTime().asSeconds() > 0.05f)
		{
			clock.restart();
		}

		window.clear();
		sf::RenderStates state;
		layout.DrawLayout(window);
		Background::DrawBackground(window);
		SpriteManager::DrawSprites(window);
		window.display();
	}

	return 0;
}
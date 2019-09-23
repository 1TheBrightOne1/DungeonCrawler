#include "Pathfinder.h"

Grid PixelToGrid(sf::Vector2f position)
{
	return Grid(position.x / TILE_SIZE, position.y / TILE_SIZE);
}

Tile GetSmallest(std::map<Grid, Tile> list)
{
	Grid smallest = list.begin()->first;
	for (const auto& x : list)
	{
		if (x.second.g + x.second.h < list[smallest].g + list[smallest].h)
			smallest = x.first;
	}
	return list[smallest];
}

Tile CreateNewTile(Tile parent, Grid location, Grid end)
{
	Tile t = Tile();
	t.location = location;
	t.g = parent.g + 1;
	t.parent = parent.location;
	t.h = abs(end.first - t.location.first) + abs(end.second - t.location.second);
	return t;
}

std::vector<sf::Vector2f> GetPath(int entityID, sf::Vector2f start, sf::Vector2f finish, bool getClosest)
{
	const int TRY_LIMIT = 10000;
	int count = 0;

	Grid a = PixelToGrid(start);
	Grid b = PixelToGrid(finish);

	if (CollisionManager::IsOccupied(-1, sf::IntRect(b.first * TILE_SIZE, b.second * TILE_SIZE, TILE_SIZE, TILE_SIZE)) && !getClosest)
		return std::vector<sf::Vector2f>();

	std::map<Grid, Tile> open;	
	std::map<Grid, Tile> closed;

	open[a] = Tile();
	open[a].location = a;
	open[a].parent = Grid(-1, -1);

	while (++count <= TRY_LIMIT)
	{
		Tile s = GetSmallest(open);
		closed[s.location] = s;
		open.erase(s.location);

		for (int i = 1; i <= 4; ++i)
		{
			Grid t;
			switch (i)
			{
			case 1:
				t = Grid(s.location.first - 1, s.location.second);
				break;
			case 2:
				t = Grid(s.location.first + 1, s.location.second);
				break;
			case 3:
				t = Grid(s.location.first, s.location.second - 1);
				break;
			case 4:
				t = Grid(s.location.first, s.location.second + 1);
				break;
			}

			if (t.first < 0 || t.second < 0 || t.first > 800 / TILE_SIZE || t.second > 800 / TILE_SIZE)
				continue;
			if (closed.find(t) != closed.end())
				continue;
			if (CollisionManager::IsOccupied(entityID, sf::IntRect(t.first * TILE_SIZE, t.second * TILE_SIZE, TILE_SIZE, TILE_SIZE)))
			{
				Tile blockedTile;
				blockedTile.location = t;
			}
			else if (open.find(t) == open.end())
			{
				open[t] = CreateNewTile(s, t, b);
			}
			else
			{
				Tile newPath = CreateNewTile(s, t, b);
				if (newPath.g + newPath.h < open[t].g + open[t].h)
					open[t] = newPath;
			}

			if (open.size() == 0)
				break;

			if (t == b || (open.empty() && i == 4 && getClosest))
			{
				std::vector<sf::Vector2f> path;
				closed[t] = open[t];
				Grid backTrack = t;
				while (1)
				{
					path.push_back(sf::Vector2f(backTrack.first * TILE_SIZE, backTrack.second * TILE_SIZE));

					backTrack = closed[backTrack].parent;
					if (closed[backTrack].parent == Grid(-1, -1))
						break;
				}
				return path;
			}
		}
	}
	return std::vector<sf::Vector2f>();
}

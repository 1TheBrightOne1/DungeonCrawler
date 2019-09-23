#include "Wall.h"


Wall::Wall(const sf::Vector2f& position) : StaticEntity("C:/users/kevin/documents/programming projects/dungeoncrawler/dungeoncrawler/assets/Tileset1.png", sf::IntRect(16, 12, TILE_SIZE, TILE_SIZE), position, true)
{
}


Wall::~Wall()
{
}
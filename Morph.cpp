#include "Morph.h"



Morph::Morph(int entityID) : Action(entityID)
{
	pointsNeeded = 1;
}


Morph::~Morph()
{
}

bool Morph::Do(const sf::Time & elapsedTime)
{
	SpriteManager::ChangeTexture(parentEntity, "C:/users/kevin/documents/programming projects/dungeoncrawler/dungeoncrawler/assets/Tileset1.png", sf::IntRect(370, 50, TILE_SIZE, TILE_SIZE));
	return true;
}
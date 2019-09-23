#include "Fireblast.h"

Fireblast::Fireblast(int parent) : CircularTarget(parent)
{
	pointsNeeded = 16;
	preview = SpriteManager::CreateSprite(-1, "C:/users/kevin/documents/programming projects/dungeoncrawler/dungeoncrawler/assets/fireball.png", sf::IntRect(0, 0, 100, 100));
	preview->sprite->setOrigin(sf::Vector2f(50, 50));

	sf::Texture texture;
	texture.loadFromFile("Assets/Fireball.png");
	animation.AddAnimation(0, AnimationManager::Builder{ texture, 61, 1000 }.SetFrameSize(sf::Vector2i(100, 100)));
	animation.SetActiveAnimation(0);
}

Fireblast::~Fireblast()
{
}

bool Fireblast::Do(const sf::Time & elapsedTime)
{
	std::vector<int> entities = this->GetAffectedEntities();
	for (auto entity : entities)
	{
		if (entity != -1)
		{
			CombatManager::GetStats(entity)->SetHP(0);
		}
	}
	return true;
}

void Fireblast::ShowPlus(const sf::Time& elapsedTime)
{
	animation.GetActiveFrame(elapsedTime, *preview->sprite);
}

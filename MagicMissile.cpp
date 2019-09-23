#include "MagicMissile.h"



MagicMissile::MagicMissile(int parent) : TargetedAction(parent)
{
	pointsNeeded = 16;
	preview = SpriteManager::CreateSprite(-1, "C:/users/kevin/documents/programming projects/dungeoncrawler/dungeoncrawler/assets/MagicMissile.png", sf::IntRect(0, 0, 100, 100));
	preview->sprite->setOrigin(sf::Vector2f(50, 50));

	sf::Texture texture;
	texture.loadFromFile("Assets/MagicMissile.png");
	animation.AddAnimation(0, AnimationManager::Builder{ texture, 56, 1000 }.SetFrameSize(sf::Vector2i(100, 100)));
	animation.SetActiveAnimation(0);
}


MagicMissile::~MagicMissile()
{
}

bool MagicMissile::Do(const sf::Time & elapsedTime)
{
	DynamicEntity* missile = new DynamicEntity("C:/users/kevin/documents/programming projects/dungeoncrawler/dungeoncrawler/assets/MagicMissile.png", sf::IntRect(0, 0, 100, 100), SpriteManager::GetSprite(parentEntity)->sprite->getPosition());
	preview->sprite->setPosition(target);
	animation.GetActiveFrame(elapsedTime, *preview->sprite);
	return false;
}

bool MagicMissile::Show(const sf::Time & elapsedTime)
{
	if (target != sf::Vector2f())
		return true;
	preview->sprite->setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
	return false;
}

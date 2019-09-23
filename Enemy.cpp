#include "Enemy.h"



Enemy::Enemy(const sf::Vector2f& position) : DynamicEntity("C:/users/kevin/documents/programming projects/dungeoncrawler/dungeoncrawler/assets/Tileset1.png", sf::IntRect(370, 50, 16, 16), position)
{
	InitAnimations();
	actionPoints = 0;
}


Enemy::~Enemy()
{
	
}

void Enemy::InitAnimations()
{
	sf::Vector2i m_charSize{ 16, 16 };
	sf::Texture texture;
	texture.loadFromFile("Assets/tileset1.png", sf::IntRect(370, 50, 16 * 4, 16));
	m_animations.AddAnimation(0, AnimationManager::Builder{ texture, 4, 10000 }.SetFrameSize(m_charSize));

	m_animations.SetActiveAnimation(0);
}

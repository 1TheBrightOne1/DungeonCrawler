#include "Player.h"


Player::Player(const sf::Vector2f& position) : DynamicEntity("C:/users/kevin/documents/programming projects/dungeoncrawler/dungeoncrawler/assets/Tileset1.png", sf::IntRect(128, 12, TILE_SIZE, TILE_SIZE), position)
{
	std::function<void(const sf::Event& event)> callback = [=](const sf::Event& event) {
		this->AddAction(std::make_shared<Fireblast>(GetEntityID()));
	};
	std::function<void(const sf::Event& event)> moveCallback = [=](const sf::Event& event) {
		this->AddAction(std::make_shared<Move>(this->GetEntityID(), this->pointsAvailable));
	};
	std::function<void(const sf::Event& event)> missileCallback = [=](const sf::Event& event) {
		this->AddAction(std::make_shared<MagicMissile>(this->GetEntityID()));
	};
	interface.reserve(50);
	interface.emplace_back("C:/users/kevin/documents/programming projects/dungeoncrawler/dungeoncrawler/assets/fireball.png", sf::IntRect(25, 25, 50, 50), "Whatever", "Whatever", moveCallback);
	interface.emplace_back("C:/users/kevin/documents/programming projects/dungeoncrawler/dungeoncrawler/assets/fireball.png", sf::IntRect(25, 25, 50, 50), "Fireball", "Whatever", callback);
	interface.emplace_back("C:/users/kevin/documents/programming projects/dungeoncrawler/dungeoncrawler/assets/fireball.png", sf::IntRect(25, 25, 50, 50), "Missile", "Whatever", missileCallback);
	Layout::SetInterface(interface);
	InitAnimations();
	m_animations.SetActiveAnimation(0);
}

Player::~Player()
{
}

void Player::InitAnimations()
{
	sf::Vector2i m_charSize{ 16, 16 };
	sf::Texture texture;
	texture.loadFromFile("Assets/tileset1.png", sf::IntRect(128, 16, 16 * 2, 16));
	m_animations.AddAnimation(0, AnimationManager::Builder{ texture, 2, 10000 }.SetFrameSize(m_charSize));

	texture.loadFromFile("Assets/tileset1.png", sf::IntRect(128, 16, 16 * 8, 16));
	m_animations.AddAnimation(1, AnimationManager::Builder{ texture, 8, 5000 }.SetFrameSize(m_charSize));
}

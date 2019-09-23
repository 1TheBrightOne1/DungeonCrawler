#include "SpriteManager.h"

std::map <int, std::weak_ptr<SpriteResource>> SpriteManager::sprites = std::map<int, std::weak_ptr<SpriteResource>>();

std::shared_ptr<SpriteResource> SpriteManager::CreateSprite(int entity, const std::string & fileName, const sf::IntRect& size)
{
	auto spriteResource = std::make_shared<SpriteResource>();
	spriteResource->sprite = std::make_shared<sf::Sprite>();
	spriteResource->texture = TextureManager::GetTexture(fileName);
	spriteResource->sprite->setTexture(*(spriteResource->texture));

	if (size != sf::IntRect())
		spriteResource->sprite->setTextureRect(size);

	sprites[entity] = spriteResource;
	return spriteResource;
}

void SpriteManager::RemoveSprite(int entityID)
{
	sprites.erase(entityID);
}

void SpriteManager::ChangeTexture(int entity, const std::string & fileName, const sf::IntRect & size)
{
	auto sprite = sprites[entity].lock();
	sprite->texture = TextureManager::GetTexture(fileName);
	sprite->sprite->setTexture(*(sprite->texture));
	sprite->sprite->setTextureRect(size);
}

void SpriteManager::DrawSprites(sf::RenderWindow & window)
{
	auto start = sprites.begin();
	while (start != sprites.end())
	{
		if (start->second.expired())
		{
			//sprites.erase(start);
		}
		else
			window.draw(*(start->second.lock()->sprite));
		++start;
	}
}
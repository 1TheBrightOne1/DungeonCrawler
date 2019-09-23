#pragma once
#include <list>
#include <memory>
#include <string>
#include <algorithm>
#include "TextureManager.h"
#include "SFML/Graphics.hpp"

struct SpriteResource
{
	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<const sf::Texture> texture;
};

class SpriteManager
{
	static std::map<int, std::weak_ptr<SpriteResource>> sprites;
public:
	static std::shared_ptr<SpriteResource> CreateSprite(int entity, const std::string& fileName, const sf::IntRect& size = sf::IntRect());
	static void RemoveSprite(int entityID);
	static SpriteResource* GetSprite(int entity) { return &*sprites[entity].lock(); }
	static const std::map<int, std::weak_ptr<SpriteResource>> GetSprites() { return sprites; }
	static void ChangeTexture(int entity, const std::string& fileName, const sf::IntRect& size = sf::IntRect());
	static void DrawSprites(sf::RenderWindow& window);
};

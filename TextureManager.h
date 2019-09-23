#pragma once
#include <map>
#include <string>
#include <memory>
#include "SFML/Graphics.hpp"

class TextureManager
{
	static std::map<std::string, std::weak_ptr<sf::Texture>> textures;
public:
	static std::shared_ptr<sf::Texture> GetTexture(const std::string& fileName);
};


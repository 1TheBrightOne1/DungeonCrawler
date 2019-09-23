#include "TextureManager.h"

std::map<std::string, std::weak_ptr<sf::Texture>> TextureManager::textures;

std::shared_ptr<sf::Texture> TextureManager::GetTexture(const std::string & fileName)
{
	std::shared_ptr<sf::Texture> sp = textures[fileName].lock();

	if (!sp)
	{
		sp = std::make_shared<sf::Texture>();
		sp->loadFromFile(fileName);
		textures[fileName] = sp;
	}
	return sp;
}
#include "Background.h"

std::map<std::string, std::pair<std::shared_ptr<sf::Texture>, sf::VertexArray>> Background::backgroundTextures = std::map<std::string, std::pair<std::shared_ptr<sf::Texture>, sf::VertexArray>>();

void Background::AppendVertex(const std::string & fileName, const sf::Vertex & vertex, const std::string& key)
{
	if (backgroundTextures.find(key) == backgroundTextures.end())
	{
		backgroundTextures[key].second = sf::VertexArray(sf::Quads);
	}
	backgroundTextures[key].first = TextureManager::GetTexture(fileName);
	backgroundTextures[key].second.append(vertex);
}

void Background::DrawBackground(sf::RenderWindow & window)
{
	for (const auto& background : backgroundTextures)
	{
		sf::RenderStates state;
		state.texture = &(*background.second.first);
		window.draw(background.second.second, state);
	}
}

void Background::ResetLayer(const std::string & key)
{
	backgroundTextures.erase(key);
}

#pragma once

#include<map>
#include<string>
#include<SFML/Graphics.hpp>
#include "StaticEntity.h"
#include "TextureManager.h"

class Background
{
	static std::map<std::string, std::pair<std::shared_ptr<sf::Texture>, sf::VertexArray>> backgroundTextures;
public:
	static void AppendVertex(const std::string& fileName, const sf::Vertex& vertex, const std::string& key="background");
	static void DrawBackground(sf::RenderWindow& window);
	static void ResetLayer(const std::string& key);
};

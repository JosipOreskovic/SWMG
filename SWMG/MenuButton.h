#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class MenuButton
{
	std::map<std::string, sf::Texture> m_Textures;
	static MenuButton* sInstance;

public:
	MenuButton();
	static sf::Texture& GetTexture(std::string const& filename);
};


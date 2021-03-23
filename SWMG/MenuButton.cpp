#include "MenuButton.h"
#include <assert.h>

MenuButton* MenuButton::sInstance = nullptr;

MenuButton::MenuButton()
{
	//assert(sInstance == nullptr);
	sInstance = this;
}


sf::Texture& MenuButton::GetTexture(std::string const& filename)
{
	auto& texMap = sInstance->m_Textures;
	auto pairFound = texMap.find(filename);
	if (pairFound != texMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto& texture = texMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include "Sprite3d.hpp"

class Card
{
	int cardNo;
	bool cardSelect;
	sf::Sprite* image;
	sf::Sprite* cardBack;

public:
	Card(int, sf::Sprite*, sf::Sprite*);
	~Card();
	int GetCardNo();
	bool GetCardSelect();
	void SetCardSelect(bool);
	void DrawCard(sf::RenderWindow* window, int cardNo, int posX, int posY, int boardW, int boardH, bool isCardSelect);
	sf::Sprite* GetImage();
	sf::Sprite* GetCardBack();
};


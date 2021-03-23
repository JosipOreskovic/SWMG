#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Sprite3d.hpp"
#include <string>

class Player
{
	int playerNo;
	sf::String name;
	int score;
	sf::Sprite* image;
	struct position
	{
		int X;
		int Y;
	};
	position playerPos;

public:
	Player(int, sf::Sprite*);
	~Player();
	int GetPlayerNo();
	sf::String GetPlayerName();
	void SetPlayerName(sf::String);
	int GetScore();
	void SetScore(int);
	int GetPlayerPosX();
	int GetPlayerPosY();
	void SetPlayerPos(int, int);
	void DrawPlayer(sf::RenderWindow*, int);
	void PrintPlayerStat(sf::RenderWindow* window);
	
};


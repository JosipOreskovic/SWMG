#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Windows.h>
#include <vector>
#include <string>
#include <cmath>
#include "Sprite3d.hpp"
#include "Card.h"
#include "Player.h"
#include "AssetManager.h"

class MemoryGame
{
	//sf::SoundBuffer buffer;
	sf::Sound flipSound, flopSound, pairSound;
	std::vector<Card*> board;
	std::vector<Player*> players;

	const int CARD_DIM = 105;
	int noOfPlayers, level, cardCounter;
	int boardW = 0, boardH = 0;
	bool flipCardFlag, flopCardFlag, gameOver;
	int firstCard, secondCard, noOfCardsSelect;
	int activePlayer;
	int cardDimension;
	float scale;
	
public:
	MemoryGame();
	~MemoryGame();
	int Start();
	int DrawMenu(sf::RenderWindow*, std::string menuType, int noOfMenuItems);
	void GameSetup(sf::RenderWindow*);
	int Play();
	void BoardSetup();
	void PlayersSetup(sf::RenderWindow*);
	sf::String EnterPlayerName(sf::RenderWindow*, int);
	void SoundSetup();
	void DrawBoard(sf::RenderWindow*);
	void DrawPlayers(sf::RenderWindow*);
	void DrawResults();
	int SelectCard(sf::RenderWindow*);
	bool checkPair(int, int);
	void Delay(float time);
	void FlipCard(sf::RenderWindow*, int);
	void GameOver();
};


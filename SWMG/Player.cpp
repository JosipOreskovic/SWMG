#include "Player.h"



Player::Player(int playerNo, sf::Sprite* image)
{
	this->playerNo = playerNo;
	this->image = image;
	this->name = "Player";
	this->score = 0;
}


Player::~Player()
{
}

int Player::GetPlayerNo()
{
	return this->playerNo;
}

sf::String Player::GetPlayerName()
{
	return this->name;
}

void Player::SetPlayerName(sf::String name)
{
	this->name = name;
}

int Player::GetScore()
{
	return this->score;
}

void Player::SetScore(int point)
{
	this->score = this->score + point;
}


int Player::GetPlayerPosX()
{
	return this->playerPos.X;
}

int Player::GetPlayerPosY()
{
	return this->playerPos.Y;
}

void Player::SetPlayerPos(int x, int y)
{
	this->playerPos.X = x;
	this->playerPos.Y = y;
}

void Player::DrawPlayer(sf::RenderWindow* window, int activePlayer)
{
	float scale;
	scale = window->getSize().y / 1200.;

	if (this->playerNo == activePlayer) image->setScale(1.f * scale, 1.f* scale);
	else image->setScale(.5f* scale, .5f* scale);

	this->image->setOrigin(sf::Vector2f(this->image->getLocalBounds().width / 2.f, this->image->getLocalBounds().height) / 2.f);
	this->image->setPosition(this->playerPos.X, this->playerPos.Y);
	window->draw(*image);

	PrintPlayerStat(window);
}

void Player::PrintPlayerStat(sf::RenderWindow* window)
{
	std::string textStr;
	sf::Text text;
	sf::Font font;
	
	float scale;
	scale = window->getSize().y / 1200.;

	if (!font.loadFromFile("resources/STARWARS.ttf"))
	{
		// error...
	}
	text.setFont(font);

	text.setString(this->name);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::Black);
	text.setPosition(this->playerPos.X + 160 * scale, playerPos.Y - 40 * scale);
	window->draw(text);

	text.setString(std::to_string(this->score));
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::Black);
	text.setPosition(this->playerPos.X + 160 * scale, playerPos.Y - 25 * scale);
	window->draw(text);

	text.setString(std::to_string(window->getSize().x));
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::Black);
	text.setPosition(100,100);
	window->draw(text);

	text.setString(std::to_string(window->getSize().y));
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::Black);
	text.setPosition(100, 150);
	window->draw(text);

}
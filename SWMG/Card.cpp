#include "Card.h"




Card::Card(int cardNo, sf::Sprite* image, sf::Sprite* cardBack)
{
	this->cardNo = cardNo;
	this->image = image;
	this->cardBack = cardBack;
	this->cardSelect = FALSE;

}


Card::~Card()
{
}

int Card::GetCardNo()
{
	return this->cardNo;
}

bool Card::GetCardSelect()
{
	return cardSelect;
}





void Card::SetCardSelect(bool cardSelect)
{
	this->cardSelect = cardSelect;
}

void Card::DrawCard(sf::RenderWindow* window, int cardNo, int posX, int posY, int boardW, int boardH, bool isCardSelect)
{
	sf::Sprite sprite;
	int cardDimension;
	
	float scale;
	scale = window->getSize().y / 1200.;
	cardDimension = 105 * scale;

	if (isCardSelect) sprite = *image;
	else sprite = *cardBack;
	
	sprite.scale(scale, scale);
	//sprite.setTextureRect(sf::IntRect(cardDimension, 0, -cardDimension, cardDimension));
	sprite.setPosition((window->getSize().x - cardDimension * boardW) / 2 + cardDimension * posX, (window->getSize().y - cardDimension * boardH) / 2 + cardDimension * posY);
	
	window->draw(sprite);
}

sf::Sprite* Card::GetImage()
{
	return this->image;
}

sf::Sprite* Card::GetCardBack()
{
	return this->cardBack;
}

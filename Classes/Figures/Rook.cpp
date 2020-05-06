#include "Rook.h"

Rook::Rook()
{
	this->color = ' ';
	this->posY = 0;
	this->posX = 0;
	this->gameMode = 8;
}

Rook::Rook(char color)
{
	this->color = color;
	this->posY = 0;
	this->posX = 0;
	this->gameMode = 8;
}

sf::Sprite Rook::getSprite()
{
	return this->sprite;
}

int Rook::getPosX()
{
	return this->posX;
}

int Rook::getPosY()
{
	return this->posY;
}

void Rook::setPosX(int x)
{
	this->posX = x;
}

void Rook::setPosY(int y)
{
	this->posY = y;
}

void Rook::setPosition(int x, int y)
{
	this->setPosX(x);
	this->setPosY(y);
}

void Rook::setGameMode(int gm)
{
	this->gameMode = gm;
}

void Rook::move()
{
	if(this->gameMode == 8)
		this->sprite.setPosition(sf::Vector2f(this->posY * 100, this->posX * 100));
	else if(this->gameMode == 12)
		this->sprite.setPosition(sf::Vector2f(this->posY * 66.66666666666667, this->posX * 66.66666666666667));
}

void Rook::initTexture()
{
	this->texture.loadFromFile("Images/chessPieces.png");
}

void Rook::initSprite()
{
	this->sprite.setTexture(this->texture);

	if (this->color == 'W')
		this->sprite.setTextureRect(sf::IntRect(0, 0, 132, 132));
	else if(this->color == 'B')
		this->sprite.setTextureRect(sf::IntRect(0, 132, 132, 132));

	if(this->gameMode == 8)
		this->sprite.setScale(sf::Vector2f(FIGURE_IMAGE_SCALAR_8x8, FIGURE_IMAGE_SCALAR_8x8));
	else if(this->gameMode == 12)
		this->sprite.setScale(sf::Vector2f(FIGURE_IMAGE_SCALAR_12x12, FIGURE_IMAGE_SCALAR_12x12));
}

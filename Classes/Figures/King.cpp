#include "King.h"

King::King()
{
	this->color = ' ';
	this->posY = 0;
	this->posX = 0;

	this->gameMode = 8;
}

King::King(char color)
{
	this->color = color;
	this->posY = 0;
	this->posX = 0;

	this->gameMode = 8;
}

sf::Sprite King::getSprite()
{
	return this->sprite;
}

int King::getPosX()
{
	return this->posX;
}

int King::getPosY()
{
	return this->posY;
}

void King::setPosX(int x)
{
	this->posX = x;
}

void King::setPosY(int y)
{
	this->posY = y;
}

void King::setPosition(int x, int y)
{
	this->setPosX(x);
	this->setPosY(y);
}

void King::setGameMode(int gm)
{
	this->gameMode = gm;
}

void King::move()
{
	if (this->gameMode == 8)
		this->sprite.setPosition(sf::Vector2f(this->posY * 100, this->posX * 100));
	else if (this->gameMode == 12)
		this->sprite.setPosition(sf::Vector2f(this->posY * 66.66666666666667, this->posX * 66.66666666666667));
}

void King::initTexture()
{
	this->texture.loadFromFile("Images/chessPieces.png");
}

void King::initSprite()
{
	this->sprite.setTexture(this->texture);

	if (this->color == 'W')
		this->sprite.setTextureRect(sf::IntRect(4 * 132, 0, 132, 132));
	else if (this->color == 'B')
		this->sprite.setTextureRect(sf::IntRect(4 * 132, 132, 132, 132));

	if (this->gameMode == 8)
		this->sprite.setScale(sf::Vector2f(FIGURE_IMAGE_SCALAR_8x8, FIGURE_IMAGE_SCALAR_8x8));
	else if (this->gameMode == 12)
		this->sprite.setScale(sf::Vector2f(FIGURE_IMAGE_SCALAR_12x12, FIGURE_IMAGE_SCALAR_12x12));
}
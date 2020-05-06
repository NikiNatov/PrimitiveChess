#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Main.hpp>
#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

#include "../Global Constants/GlobalConstants.h"

class King
{
public:
	// Constructors
	King();
	King(char color);

	// Getters
	sf::Sprite getSprite();
	int getPosX();
	int getPosY();

	// Updated the piece position
	void setPosition(int x, int y);
	void setGameMode(int gm);

	// Moves the piece
	void move();

	// Initializers
	void initTexture();
	void initSprite();

private:
	// Sets X and Y positions
	void setPosX(int x);
	void setPosY(int y);
private:
	// Objects
	sf::Texture texture;
	sf::Sprite sprite;

	int gameMode;
	char color;
	int posX, posY;
};
#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Main.hpp>
#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

#include "../Global Constants/GlobalConstants.h"
#include <iostream>
#include <ctime>

class Board
{
public:
	// Constructors and destructors
	Board();
	Board(int size);
	~Board();

	// Getter functions
	sf::Sprite getSprite();
	int getBoardSize();
	char** getBoard();

	// Board utility functions
	void updateBoard(int x, int y, char piece);
	void printBoard();

	// Functions that place the figures on random spots on the board
	void placeKings();
	void placeRooks();

	// Sets up the chessboard
	void createBoard(int size = 8);
	void setBoardSize(int size);

	// Initializers
	void initTexture();
	void initSprite();

	sf::Texture texture1;
	sf::Texture texture2;
private:
	
	sf::Sprite sprite1;
	sf::Sprite sprite2;

	char** board;
	int boardSize;
};


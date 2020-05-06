#include "Board.h"

Board::Board()
{
	srand(time(0));
	this->boardSize = 0;
	this->board = nullptr;

	this->createBoard();
}

Board::Board(int size)
{
	srand(time(0));
	this->boardSize = size;
	this->board = nullptr;

	this->createBoard();
}

Board::~Board()
{
	for (int i = 0; i < this->boardSize; i++)
	{
		delete[] this->board[i];
	}
	delete[] this->board;
}

sf::Sprite Board::getSprite()
{
	if (this->boardSize == 8)
		return this->sprite1;
	else if (this->boardSize == 12)
		return this->sprite2;
}

int Board::getBoardSize()
{
	return this->boardSize;
}

char** Board::getBoard()
{
	return this->board;
}

void Board::updateBoard(int x, int y, char piece)
{
	for (int i = 0; i < this->boardSize; i++)
	{
		for (int j = 0; j < this->boardSize; j++)
		{
			if (this->board[i][j] == piece)
			{
				board[x][y] = piece;
				board[i][j] = ' ';

				return;
			}
		}
	}

	this->printBoard();
}

void Board::printBoard()
{
	if (this->boardSize == 8)
	{
		std::cout << "     A   B   C   D   E   F   G   H" << std::endl;
		std::cout << "   ---------------------------------" << std::endl;
		for (int i = 0; i < this->boardSize; i++)
		{
			for (int j = 0; j < this->boardSize; j++)
			{
				if (j == 0)
					std::cout << " " << 8 - i << " | " << this->board[i][j];
				if (j > 0 && j < this->boardSize - 1)
					std::cout << " | " << this->board[i][j];
				if (j == this->boardSize - 1)
					std::cout << " | " << this->board[i][j] << " |";
			}
			std::cout << " " << 8 - i << std::endl << "   ---------------------------------" << std::endl;
		}
		std::cout << "     A   B   C   D   E   F   G   H" << std::endl;
	}
	else if (this->boardSize == 12)
	{
		std::cout << "      A   B   C   D   E   F   G   H   I   J   K   L" << std::endl;
		std::cout << "    -------------------------------------------------" << std::endl;
		for (int i = 0; i < this->boardSize; i++)
		{
			for (int j = 0; j < this->boardSize; j++)
			{
				if (j == 0)
				{
					if (i == 0 || i == 1 || i == 2)
						std::cout << " " << 12 - i << " | " << this->board[i][j];
					else
						std::cout << " " << 12 - i << "  | " << this->board[i][j];
				}
				if (j > 0 && j < this->boardSize - 1)
					std::cout << " | " << this->board[i][j];
				if (j == this->boardSize - 1)
					std::cout << " | " << this->board[i][j] << " |";
			}
			std::cout << " " << 12 - i << std::endl << "    -------------------------------------------------" << std::endl;
		}
		std::cout << "      A   B   C   D   E   F   G   H   I   J   K   L" << std::endl;
	}
}

void Board::initTexture()
{
	this->texture1.loadFromFile("Images/chessBoardGrey.png");
	this->texture2.loadFromFile("Images/chessBoardGrey12x12.png");
}

void Board::initSprite()
{
	if (this->boardSize == 8)
	{
		this->sprite1.setTexture(this->texture1);
		this->sprite1.setScale(sf::Vector2f(BOARD_IMAGE_SCALAR_8x8, BOARD_IMAGE_SCALAR_8x8));
	}
	if (this->boardSize == 12)
	{
		this->sprite2.setTexture(this->texture2);
		this->sprite2.setScale(sf::Vector2f(BOARD_IMAGE_SCALAR_12x12, BOARD_IMAGE_SCALAR_12x12));
	}
}

void Board::createBoard(int size)
{
	this->boardSize = size;
	this->board = new char* [size];

	for (int i = 0; i < this->boardSize; i++)
	{
		this->board[i] = new char[this->boardSize];
	}

	for (int i = 0; i < this->boardSize; i++)
	{
		for (int j = 0; j < this->boardSize; j++)
		{
			this->board[i][j] = ' ';
		}
	}

	this->placeKings();
	this->placeRooks();
}

void Board::setBoardSize(int size)
{
	this->boardSize = size;
}

void Board::placeKings()
{
	while (1)
	{
		int x1 = rand() % this->boardSize;
		int x2 = rand() % this->boardSize;
		int y1 = rand() % this->boardSize;
		int y2 = rand() % this->boardSize;

		if (x1 != x2 && abs(x1 - x2) > 1 && abs(y1 - y2) > 1)
		{
			this->board[x1][y1] = 'K';
			this->board[x2][y2] = 'k';
			return;
		}
	}
}

void Board::placeRooks()
{
	while (1)
	{
		int x1 = rand() % this->boardSize;
		int x2 = rand() % this->boardSize;
		int y1 = rand() % this->boardSize;
		int y2 = rand() % this->boardSize;

		bool isInCheck = false;

		if (x1 != x2)
		{
			for (int i = 0; i < this->boardSize; i++)
			{
				if (this->board[x1][i] == 'k' || this->board[i][y1] == 'k' || this->board[x2][i] == 'k' || this->board[i][y2] == 'k')
					isInCheck = true;
			}

			if (isInCheck == false)
			{
				if (this->board[x1][y1] != 'K' && this->board[x1][y1] != 'k' && this->board[x2][y2] != 'K' && this->board[x2][y2] != 'k')
				{
					this->board[x1][y1] = '1';
					this->board[x2][y2] = '2';
					return;
				}
			}
		}
	}
}

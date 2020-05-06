#include "Chess.h"

Chess::Chess()
{

	this->isRookCaptured[0] = 0;
	this->isRookCaptured[1] = 0;

	this->isGameOver = false;
	this->boardSize = 8;
	this->col = 0;
	this->row = 0;
	this->inputFile = ' ';
	this->inputPiece = ' ';
	this->inputRank = 0;
	this->menuChoice = ' ';
	this->movesMade = 0;
	this->isDraw = false;
	this->isMate = false;
}

// Main running function
void Chess::run()
{
	this->printMenu();

	// Asks the user to enter a choice from the menu
	do
	{
		std::cout << "Enter choice: ";
		std::cin >> this->menuChoice;
		std::cout << std::endl;
	} while (this->menuChoice != '1' && this->menuChoice != '2' && this->menuChoice != 'q');

	// Option 1: Start new game
	if (this->menuChoice == '1')
	{
		this->board.createBoard(this->boardSize);

		this->rook1.setGameMode(this->boardSize);
		this->rook2.setGameMode(this->boardSize);

		// Initialize rook textures
		this->rook1.initTexture();
		this->rook1.initSprite();
		this->rook2.initTexture();
		this->rook2.initSprite();

		this->kingW.setGameMode(this->boardSize);
		this->kingB.setGameMode(this->boardSize);

		// Initialize king textures
		this->kingW.initTexture();
		this->kingW.initSprite();
		this->kingB.initTexture();
		this->kingB.initSprite();


		// Initialize board textures
		this->board.initTexture();
		this->board.initSprite();

		this->loadStartingPosition();

		this->board.printBoard();

		this->drawSprites();

		while (this->renderer.window->isOpen() && this->isGameOver == false)
		{
			// Game functions
			this->movePiece();
			
			// If the user enters 'q' then we quit the game
			if (this->inputPiece == 'q')
				break;

			// Checks if the move is possible
			this->checkForLegalMove();

			// Moves the selected piece to the selected coordinates on the console board
			this->board.updateBoard(this->row, this->col, this->inputPiece);

			// Moves the selected piece to the selected coordinates on the graphical board
			this->updatePosition();

			// The computer moves
			this->aiMove();

			// Increases the moves count
			this->movesMade++;

			// If both rooks are captured then the game is drawn and we quit
			if (this->isRookCaptured[0] == true && this->isRookCaptured[1] == true)
			{
				std::cout << std::endl << "Draw!" << std::endl;
				std::cout << "Moves made: " << this->movesMade << std::endl;

				this->isDraw = true;
				this->isGameOver = true;
			}

			this->board.printBoard();

			// Rendering
			this->drawSprites();
		}

		// Resets all variables after the game is over and returns to the main menu
		this->reset();
		this->run();
	}

	// Option 2: Resize Board
	else if (this->menuChoice == '2')
	{
		std::cout << "Enter board size: ";
		do
		{
			std::cin >> this->boardSize;
		} while (this->boardSize != 8 && this->boardSize != 12);
		
		this->run();
	}

	// Option 3: Quit
	else if (this->menuChoice == 'q')
	{
		return;
	}
}

// Reset variables
void Chess::reset()
{
	this->isRookCaptured[0] = 0;
	this->isRookCaptured[1] = 0;

	this->isGameOver = false;
	this->col = 0;
	this->row = 0;
	this->inputFile = ' ';
	this->inputPiece = ' ';
	this->inputRank = 0;
	this->menuChoice = ' ';
	this->movesMade = 0;
	this->isDraw = false;
	this->isMate = false;
	
	for (int i = 0; i < this->boardSize; i++)
		for (int j = 0; j < this->boardSize; j++)
			this->board.getBoard()[i][j] = ' ';

	this->board.placeKings();
	this->board.placeRooks();
}

// Render sprites
void Chess::drawSprites()
{
	// Rendering
	this->renderer.update();
	this->renderer.window->clear();

	this->renderer.drawSprite(this->board.getSprite());

	if (this->isRookCaptured[0] == false)
		this->renderer.drawSprite(this->rook1.getSprite());
	if (this->isRookCaptured[1] == false)
		this->renderer.drawSprite(this->rook2.getSprite());

	this->renderer.drawSprite(this->kingW.getSprite());
	this->renderer.drawSprite(this->kingB.getSprite());

	if (this->isDraw == true)
	{
		this->renderer.textMessage.setString("Draw!");
		this->renderer.textMessage.setPosition(sf::Vector2f(290.0f, 350.0f));
		this->renderer.textMessage.setFillColor(sf::Color::Red);
		this->renderer.window->draw(renderer.textMessage);
	}
	else if (this->isMate == true)
	{
		this->renderer.textMessage.setString("Checkmate!");
		this->renderer.textMessage.setPosition(sf::Vector2f(180.0f, 350.0f));
		this->renderer.textMessage.setFillColor(sf::Color::Green);
		this->renderer.window->draw(renderer.textMessage);
	}

	this->renderer.window->display();
}

// Move white pieces
void Chess::movePiece()
{
	if (this->boardSize == 8)
	{
		do
		{
			std::cout << "Enter a piece: ";
			std::cin >> this->inputPiece;
		} while (this->inputPiece != 'K' && this->inputPiece != '1' && this->inputPiece != '2' && this->inputPiece != 'q');

		do
		{
			std::cout << "Enter file(A - H): ";
			std::cin >> this->inputFile;
		} while (this->inputFile < 'A' || this->inputRank > 'H');

		do
		{
			std::cout << "Enter rank(1 - 8): ";
			std::cin >> this->inputRank;
		} while (this->inputRank < 1 || this->inputRank > 8);

		this->col = this->inputFile - 'A';
		this->row = 8 - this->inputRank;
	}
	else if (this->boardSize == 12)
	{
		do
		{
			std::cout << "Enter a piece: ";
			std::cin >> this->inputPiece;
		} while (this->inputPiece != 'K' && this->inputPiece != '1' && this->inputPiece != '2' && this->inputPiece != 'q');

		do
		{
			std::cout << "Enter file(A - L): ";
			std::cin >> this->inputFile;
		} while (this->inputFile < 'A' || this->inputRank > 'L');

		do
		{
			std::cout << "Enter rank(1 - 12): ";
			std::cin >> this->inputRank;
		} while (this->inputRank < 1 || this->inputRank > 12);

		this->col = this->inputFile - 'A';
		this->row = 12 - this->inputRank;
	}

	this->checkForLegalMove();
}

// AI move
void Chess::aiMove()
{
	// Checks if rook 1 can be captured
	if (((this->kingB.getPosX() + 1 == this->rook1.getPosX() && this->kingB.getPosY() == this->rook1.getPosY()) ||
		(this->kingB.getPosX() - 1 == this->rook1.getPosX() && this->kingB.getPosY() == this->rook1.getPosY()) ||
		(this->kingB.getPosY() + 1 == this->rook1.getPosY() && this->kingB.getPosX() == this->rook1.getPosX()) ||
		(this->kingB.getPosY() - 1 == this->rook1.getPosY() && this->kingB.getPosX() == this->rook1.getPosX()) ||
		(this->kingB.getPosX() + 1 == this->rook1.getPosX() && this->kingB.getPosY() + 1 == this->rook1.getPosY()) ||
		(this->kingB.getPosX() + 1 == this->rook1.getPosX() && this->kingB.getPosY() - 1 == this->rook1.getPosY()) ||
		(this->kingB.getPosX() - 1 == this->rook1.getPosX() && this->kingB.getPosY() + 1 == this->rook1.getPosY()) ||
		(this->kingB.getPosX() - 1 == this->rook1.getPosX() && this->kingB.getPosY() - 1 == this->rook1.getPosY())) && 
		this->checkForCheck(this->rook1.getPosX(), this->rook1.getPosY()) == false)
	{
		this->kingB.setPosition(this->rook1.getPosX(), this->rook1.getPosY());
		this->kingB.move();
		this->board.updateBoard(this->kingB.getPosX(), this->kingB.getPosY(), 'k');
		this->rook1.setPosition(-1000, -1000);
		this->rook1.move();
		this->isRookCaptured[0] = 1;
	}

	// Checks if rook 2 can be captured
	else if (((this->kingB.getPosX() + 1 == this->rook2.getPosX() && this->kingB.getPosY() == this->rook2.getPosY()) ||
		(this->kingB.getPosX() - 1 == this->rook2.getPosX() && this->kingB.getPosY() == this->rook2.getPosY()) ||
		(this->kingB.getPosY() + 1 == this->rook2.getPosY() && this->kingB.getPosX() == this->rook2.getPosX()) ||
		(this->kingB.getPosY() - 1 == this->rook2.getPosY() && this->kingB.getPosX() == this->rook2.getPosX()) ||
		(this->kingB.getPosX() + 1 == this->rook2.getPosX() && this->kingB.getPosY() + 1 == this->rook2.getPosY()) ||
		(this->kingB.getPosX() + 1 == this->rook2.getPosX() && this->kingB.getPosY() - 1 == this->rook2.getPosY()) ||
		(this->kingB.getPosX() - 1 == this->rook2.getPosX() && this->kingB.getPosY() + 1 == this->rook2.getPosY()) ||
		(this->kingB.getPosX() - 1 == this->rook2.getPosX() && this->kingB.getPosY() - 1 == this->rook2.getPosY())) &&
		this->checkForCheck(this->rook2.getPosX(), this->rook2.getPosY()) == false)
	{
		this->kingB.setPosition(this->rook2.getPosX(), this->rook2.getPosY());
		this->kingB.move();
		this->board.updateBoard(this->kingB.getPosX(), this->kingB.getPosY(), 'k');
		this->rook2.setPosition(-1000, -1000);
		this->rook2.move();
		this->isRookCaptured[1] = 1;
	}

	// If none of the rooks and be captured check for other possible moves
	else
	{
		// Move down
		if (this->checkForCheck(this->kingB.getPosX() + 1, this->kingB.getPosY()) == false && this->kingB.getPosX() + 1 <= this->boardSize - 1)
		{
			this->kingB.setPosition(this->kingB.getPosX() + 1, this->kingB.getPosY());
			this->kingB.move();
			this->board.updateBoard(this->kingB.getPosX(), this->kingB.getPosY(), 'k');
		}

		// Move up
		else if (this->checkForCheck(this->kingB.getPosX() - 1, this->kingB.getPosY()) == false && this->kingB.getPosX() - 1 >= 0)
		{
			this->kingB.setPosition(this->kingB.getPosX() - 1, this->kingB.getPosY());
			this->kingB.move();
			this->board.updateBoard(this->kingB.getPosX(), this->kingB.getPosY(), 'k');
		}

		// Move right
		else if (this->checkForCheck(this->kingB.getPosX(), this->kingB.getPosY() + 1) == false && this->kingB.getPosY() + 1 <= this->boardSize - 1)
		{
			this->kingB.setPosition(this->kingB.getPosX(), this->kingB.getPosY() + 1);
			this->kingB.move();
			this->board.updateBoard(this->kingB.getPosX(), this->kingB.getPosY(), 'k');
		}

		// Move left
		else if (this->checkForCheck(this->kingB.getPosX(), this->kingB.getPosY() - 1) == false && this->kingB.getPosY() - 1 >= 0)
		{
			this->kingB.setPosition(this->kingB.getPosX(), this->kingB.getPosY() - 1);
			this->kingB.move();
			this->board.updateBoard(this->kingB.getPosX(), this->kingB.getPosY(), 'k');
		}

		// Move down and right
		else if (this->checkForCheck(this->kingB.getPosX() + 1, this->kingB.getPosY() + 1) == false && 
			(this->kingB.getPosX() + 1 <= this->boardSize - 1 && this->kingB.getPosY() + 1 <= this->boardSize - 1))
		{
			this->kingB.setPosition(this->kingB.getPosX() + 1, this->kingB.getPosY() + 1);
			this->kingB.move();
			this->board.updateBoard(this->kingB.getPosX(), this->kingB.getPosY(), 'k');
		}

		// Move down and left
		else if (this->checkForCheck(this->kingB.getPosX() + 1, this->kingB.getPosY() - 1) == false &&
			(this->kingB.getPosX() + 1 <= this->boardSize - 1 && this->kingB.getPosY() - 1 >= 0))
		{
			this->kingB.setPosition(this->kingB.getPosX() + 1, this->kingB.getPosY() - 1);
			this->kingB.move();
			this->board.updateBoard(this->kingB.getPosX(), this->kingB.getPosY(), 'k');
		}

		// Move up and left
		else if (this->checkForCheck(this->kingB.getPosX() - 1, this->kingB.getPosY() - 1) == false &&
			(this->kingB.getPosX() - 1 >= 0 && this->kingB.getPosY() - 1 >= 0))
		{
			this->kingB.setPosition(this->kingB.getPosX() - 1, this->kingB.getPosY() - 1);
			this->kingB.move();
			this->board.updateBoard(this->kingB.getPosX(), this->kingB.getPosY(), 'k');
		}

		// Move up and right
		else if (this->checkForCheck(this->kingB.getPosX() - 1, this->kingB.getPosY() + 1) == false &&
			(this->kingB.getPosX() - 1 >= 0 && this->kingB.getPosY() + 1 <= this->boardSize - 1))
		{
			this->kingB.setPosition(this->kingB.getPosX() - 1, this->kingB.getPosY() + 1);
			this->kingB.move();
			this->board.updateBoard(this->kingB.getPosX(), this->kingB.getPosY(), 'k');
		}

		// If none of the moves is possible check if it is a stalemate or checkmate
		else
		{
			// If the king is in check then it is checkmate
			if (this->checkForCheck(this->kingB.getPosX(), this->kingB.getPosY()) == true)
			{
				std::cout << std::endl << "Checkmate!" << std::endl;
				std::cout << "Moves made: " << this->movesMade << std::endl;

				this->isMate = true;
				this->isGameOver = true;
			}

			// If the king is not in check and cannot move then it is a stalemate
			else
			{
				std::cout << std::endl << "Draw!" << std::endl;
				std::cout << "Moves made: " << this->movesMade << std::endl;

				this->isDraw = true;
				this->isGameOver = true;
			}
		}
	}
}

// Loads figures starting positions
void Chess::loadStartingPosition()
{
	for (int i = 0; i < this->boardSize; i++)
	{
		for (int j = 0; j < this->boardSize; j++)
		{
			switch (this->board.getBoard()[i][j])
			{
			case '1':
				this->rook1.setPosition(i, j);
				this->rook1.move();
				break;
			case '2':
				this->rook2.setPosition(i, j);
				this->rook2.move();
				break;
			case 'K':
				this->kingW.setPosition(i, j);
				this->kingW.move();
				break;
			case 'k':
				this->kingB.setPosition(i, j);
				this->kingB.move();
				break;
			}
		}
	}
}

// Loads the updated position of a selected piece
void Chess::updatePosition()
{
	switch (this->inputPiece)
	{
	case '1':
		this->rook1.setPosition(this->row, this->col);
		this->rook1.move();
		break;
	case '2':
		this->rook2.setPosition(this->row, this->col);
		this->rook2.move();
		break;
	case 'K':
		this->kingW.setPosition(this->row, this->col);
		this->kingW.move();
		break;
	case 'k':
		this->kingB.setPosition(this->row, this->col);
		this->kingB.move();
		break;
	}
}

// Checks if the black king is in check on the selected board position
bool Chess::checkForCheck(int x, int y)
{
	// Check if a rook and the black king are on the same file / rank
	if ((this->rook1.getPosX() == x && this->rook1.getPosY() != y ) || (this->rook1.getPosY() == y && this->rook1.getPosX() != x) || 
		(this->rook2.getPosX() == x && this->rook2.getPosY() != y) || (this->rook2.getPosY() == y && this->rook2.getPosX() != x))
	{
		return true;
	}

	// Check if the white king is blocking the black king's movement
	else if ((x + 1 == this->kingW.getPosX() && y == this->kingW.getPosY()) || (x - 1 == this->kingW.getPosX() && y == this->kingW.getPosY()) ||
		(x == this->kingW.getPosX() && y + 1 == this->kingW.getPosY()) || (x == this->kingW.getPosX() && y - 1 == this->kingW.getPosY()) ||
		(x + 1 == this->kingW.getPosX() && y + 1 == this->kingW.getPosY()) || (x + 1 == this->kingW.getPosX() && y - 1 == this->kingW.getPosY()) ||
		(x - 1 == this->kingW.getPosX() && y + 1 == this->kingW.getPosY()) || (x - 1 == this->kingW.getPosX() && y - 1 == this->kingW.getPosY()))
	{
		return true;
	}

	return false;
}

// Check if the selected move is allowed
void Chess::checkForLegalMove()
{
	switch (this->inputPiece)
	{
	case '1':
		if (// Check if the rook is moving in a straight line
			(this->row != this->rook1.getPosX() && this->col != this->rook1.getPosY()) ||
			(this->row == this->rook2.getPosX() && this->col == this->rook2.getPosY()) ||
			// Check if the king is blocking the rook
			(this->rook1.getPosX() == this->kingW.getPosX() && this->rook1.getPosY() < this->kingW.getPosY() && this->col >= this->kingW.getPosY()) ||
			(this->rook1.getPosX() == this->kingW.getPosX() && this->rook1.getPosY() > this->kingW.getPosY() && this->col <= this->kingW.getPosY()) ||
			(this->rook1.getPosY() == this->kingW.getPosY() && this->rook1.getPosX() < this->kingW.getPosX() && this->row >= this->kingW.getPosX()) ||
			(this->rook1.getPosY() == this->kingW.getPosY() && this->rook1.getPosX() > this->kingW.getPosX() && this->row <= this->kingW.getPosX()) ||
			// Check if the other rook is blocking the rook
			(this->rook1.getPosX() == this->rook2.getPosX() && this->rook1.getPosY() < this->rook2.getPosY() && this->col >= this->rook2.getPosY()) ||
			(this->rook1.getPosX() == this->rook2.getPosX() && this->rook1.getPosY() > this->rook2.getPosY() && this->col <= this->rook2.getPosY()) ||
			(this->rook1.getPosY() == this->rook2.getPosY() && this->rook1.getPosX() < this->rook2.getPosX() && this->row >= this->rook2.getPosX()) ||
			(this->rook1.getPosY() == this->rook2.getPosY() && this->rook1.getPosX() > this->rook2.getPosX() && this->row <= this->rook2.getPosX()) ||
			// Check if the rook is already on that position
			(this->row == this->rook1.getPosX() && this->col == this->rook1.getPosY()))
		{
			std::cout << std::endl << "Rook cannot move there!" << std::endl;
			this->movePiece();
		}
		break;
	case '2':
		if (// Check if the rook is moving in a straight line
			(this->row != this->rook2.getPosX() && this->col != this->rook2.getPosY()) || 
			(this->row == this->rook1.getPosX() && this->col == this->rook1.getPosY()) ||
			// Check if the king is blocking the rook
			(this->rook2.getPosX() == this->kingW.getPosX() && this->rook2.getPosY() < this->kingW.getPosY() && this->col >= this->kingW.getPosY()) ||
			(this->rook2.getPosX() == this->kingW.getPosX() && this->rook2.getPosY() > this->kingW.getPosY() && this->col <= this->kingW.getPosY()) ||
			(this->rook2.getPosY() == this->kingW.getPosY() && this->rook2.getPosX() < this->kingW.getPosX() && this->row >= this->kingW.getPosX()) ||
			(this->rook2.getPosY() == this->kingW.getPosY() && this->rook2.getPosX() > this->kingW.getPosX() && this->row <= this->kingW.getPosX()) ||
			// Check if the other rook is blocking the rook
			(this->rook2.getPosX() == this->rook1.getPosX() && this->rook2.getPosY() < this->rook1.getPosY() && this->col >= this->rook1.getPosY()) ||
			(this->rook2.getPosX() == this->rook1.getPosX() && this->rook2.getPosY() > this->rook1.getPosY() && this->col <= this->rook1.getPosY()) ||
			(this->rook2.getPosY() == this->rook1.getPosY() && this->rook2.getPosX() < this->rook1.getPosX() && this->row >= this->rook1.getPosX()) ||
			(this->rook2.getPosY() == this->rook1.getPosY() && this->rook2.getPosX() > this->rook1.getPosX() && this->row <= this->rook1.getPosX()) ||
			// Check if the rook is already on that position
			(this->row == this->rook2.getPosX() && this->col == this->rook2.getPosY()))
		{
			std::cout << std::endl << "Rook cannot move there!" << std::endl;
			this->movePiece();
		}
		break;
	case 'K':
		if (// Check if the black king is next to the white king
			((this->row > this->kingW.getPosX() + 1) || (this->row < this->kingW.getPosX() - 1) || 
			(this->col > this->kingW.getPosY() + 1) || (this->col < this->kingW.getPosY() - 1)) || 
			 (this->row == this->kingW.getPosX() && this->col == this->kingW.getPosY()) ||		
			(this->row + 1 == this->kingB.getPosX() && this->col == this->kingB.getPosY()) || 
			(this->row - 1 == this->kingB.getPosX() && this->col == this->kingB.getPosY()) ||
			(this->row == this->kingB.getPosX() && this->col + 1 == this->kingB.getPosY()) || 
			(this->row == this->kingB.getPosX() && this->col - 1 == this->kingB.getPosY()) ||
			(this->row + 1 == this->kingB.getPosX() && this->col + 1 == this->kingB.getPosY()) ||
			(this->row + 1 == this->kingB.getPosX() && this->col - 1 == this->kingB.getPosY()) ||
			(this->row - 1 == this->kingB.getPosX() && this->col + 1 == this->kingB.getPosY()) || 
			(this->row - 1 == this->kingB.getPosX() && this->col - 1 == this->kingB.getPosY()) ||
			// Check if there is a piece on that position
			(this->row == this->rook1.getPosX() && this->col == this->rook1.getPosY()) ||
			(this->row == this->rook2.getPosX() && this->col == this->rook2.getPosY()) ||
			(this->row == this->kingB.getPosX() && this->col == this->kingB.getPosY()) ||
			// Check if the king is already on that position
			(this->row == this->kingW.getPosX() && this->col == this->kingW.getPosY()))
		{
			std::cout << std::endl << "King cannot move there!" << std::endl;
			this->movePiece();
		}
		break;
	}
}

// Menu printing function
void Chess::printMenu()
{
	std::cout << " _____________________________________" << std::endl;
	std::cout << "|                                     |" << std::endl;
	std::cout << "|                Menu                 |" << std::endl;
	std::cout << "|_____________________________________|" << std::endl;
	std::cout << "|                                     |" << std::endl;
	std::cout << "| Enter '1' to start a new game.      |" << std::endl;
	std::cout << "| Enter '2' to change the board size. |" << std::endl;
	std::cout << "| Enter 'q' to quit.                  |" << std::endl;
	std::cout << "|_____________________________________|" << std::endl << std::endl;
}

#pragma once

#include "..\Graphics Engine\Renderer.h"
#include "..\Board\Board.h"
#include "..\Figures\Rook.h"
#include "..\Figures\King.h"

class Chess
{
public:
	Chess();

	// Main running function containing the game loop
	void run();

	// Resets all variables to their default values
	void reset();

	// Handles the drawing process
	void drawSprites();

	// Function for moving the pieces
	void movePiece();  // Function for moving white
	void aiMove();	// Function for moving black

	// Pieces position updating functions
	void loadStartingPosition(); // Loads the starting board state
	void updatePosition();	// Updates the position of the moved piece

	// Checking if the black king is in check on the entered coordinates
	bool checkForCheck(int x, int y);

	// Checking if the selected piece can do the entered move
	void checkForLegalMove();

	// Function handling the menu choice
	void printMenu();

private:
	// Position and board size
	int row;	// Stores the converted value of the rows coordinates entered by the user
	int col;	// Stores the converted value of the cols coordinates entered by the user
	int boardSize; // Stores the board size

	// Input
	char inputPiece;	// Stores the input piece signature
	int inputRank;	// Stores non-converted value of the row index selected by the user
	char inputFile; // Stores non-converted value of the column index selected by the user
	char menuChoice; // Storing the choice of the main manu options

	// Logic
	bool isGameOver;
	bool isRookCaptured[2];	// Stores true if a rook is captured
	int movesMade;
	bool isDraw;
	bool isMate;

	// Objects
	Renderer renderer;
	Board board;

	Rook rook1 = Rook('W');
	Rook rook2 = Rook('W');
	King kingW = King('W');
	King kingB = King('B');	
};
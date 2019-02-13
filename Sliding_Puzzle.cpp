#pragma warning(disable:4996)

#include <iostream>				// for general IO
#include <iomanip>				// for setw()
using namespace std;

#include <string.h>				// for strcpy()
#include <conio.h>				// for getche()

#include <windows.h>			// for COLOR!

#define NUM_ROWS		3		// should not be changed for this solution
#define NUM_COLS		3		// should not be changed for this soultion

#define PIVOT -1				// used to mark the pivot spot (blank area) on the puzzle
#define PIVOT_SYMBOL	'*'		// used to show the pivot location when drawing the board

// direction codes (part of the slideTile() interface)
#define SLIDE_UP		8		// pass to slideTile() to trigger UP movement
#define SLIDE_DOWN		2		// pass to slideTile() to trigger DOWN movement
#define SLIDE_LEFT		4		// pass to slideTile() to trigger LEFT movement
#define SLIDE_RIGHT		6		// pass to slideTile() to trigger RIGHT movement

#define UNSET			-1		// used to arbitrarily indicate an undetermined state in a constuct

#define COLOR_DEFAULT	7
#define COLOR_RED		12
#define COLOR_GREEN		10


// PROTOTYPES
void InitializeBoard(char[NUM_ROWS][NUM_COLS]);
void PrintBoard(char[NUM_ROWS][NUM_COLS]);
bool slideTile(char[NUM_ROWS][NUM_COLS], int);
void scrambleBoard(char[NUM_ROWS][NUM_COLS]);		// depends upon slideTile()
bool isBoardSolved(char[NUM_ROWS][NUM_COLS]);		// indicates if the board is in the SOLVED state

													// DEVELOPMENT EXTRAS
void printTheRainbow();								// A little reminder on how to do color with the Windows API.


int main() {
	// Declarations
	char slidingBoard[NUM_ROWS][NUM_COLS];		// the board that holds the sliding tiles
	char keyStroke = ' ';						// holds the user's keystrokes as they come in
	int directionCode = UNSET;					// used to build a direction code to be sent to slideTile()

	InitializeBoard(slidingBoard);				// initializes the board
	PrintBoard(slidingBoard);					// prints the board

	while (isBoardSolved(slidingBoard) == false) {
		cout << endl << "what direction would you like to move?: " << endl;
		cin >> directionCode;
													// Seed the Pseudo-Random Number Generator (system clock)
		slideTile(slidingBoard, directionCode);
		PrintBoard(slidingBoard);
													// Driver Logic
													// 1.) This is the part where you show the board, get the moves, process the moves, and re-draw
													//  the board each time something changes.  This is the core logic of the simulation and
													//  none of the problem specific calculations should take place in main().  Instead,
													//  main() should consist of a series of controlled calls to your functions that
													//  orchestrate the top-level behavior of the simulation.
		
	}
	system("cls"); //clears the screen
	_getch();											// Exit
	return 0;
}

void InitializeBoard(char theBoard[NUM_ROWS][NUM_COLS]) {
	// YOUR IMPLEMENTATION GOES HERE...
	int counter = 49; // start at ascii code for '0'
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			if (counter == 57) { // if the counter equals the ascii code for '9' make the last box the pivot symbol
				theBoard[i][j] = PIVOT_SYMBOL;
			}
			else {
				theBoard[i][j] = counter++;
			}
		}
	}
}

void PrintBoard(char theBoard[NUM_ROWS][NUM_COLS]) {
	// YOUR IMPLEMENTATION GOES HERE...

	for (int i = 0; i < NUM_ROWS; i++) {
		cout << endl;
		for (int j = 0; j < NUM_COLS; j++) {
			cout << theBoard[i][j] << "|";
		}
	}
}

bool slideTile(char theBoard[NUM_ROWS][NUM_COLS], int slideDirection) {
	// YOUR IMPLEMENTATION GOES HERE...
	int temp = 0;
	int emptyRow = 0;
	int emptyCol = 0;

	for (int i = 0; i < NUM_ROWS; i++) {
		for(int j = 0; j < NUM_COLS; j++) {
			if (theBoard[i][j] == PIVOT_SYMBOL) {
				emptyRow = i;
				emptyCol = j;
			
			}
		}
	}
	switch (slideDirection) {
	case SLIDE_UP: {
		theBoard[emptyRow][emptyCol] = theBoard[emptyRow + 1][emptyCol];
		theBoard[emptyRow - 1][emptyCol] = PIVOT_SYMBOL;

	}
	}
	return false;
}

void scrambleBoard(char theBoard[NUM_ROWS][NUM_COLS]) {
	// YOUR IMPLEMENTATION GOES HERE...
}

bool isBoardSolved(char amISolved[NUM_ROWS][NUM_COLS]) {
	// YOUR IMPLEMENTATION GOES HERE...
	return false;
}

// EXTRAS
void printTheRainbow() {
	int currentColor = 7;

	// get the handle for the console
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// exhaustively print the colors
	cout << left;
	for (currentColor = 0; currentColor <= 255; currentColor++) {
		SetConsoleTextAttribute(hConsole, currentColor);
		cout << setw(5) << currentColor << "Look at the pretty COLORS!" << endl;
	}
}

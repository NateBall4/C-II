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
#define PIVOT_SYMBOL	0		// used to show the pivot location when drawing the board

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
void InitializeBoard(int[NUM_ROWS][NUM_COLS]);
void PrintBoard(int[NUM_ROWS][NUM_COLS], HANDLE);
bool slideTile(int[NUM_ROWS][NUM_COLS], int);
void scrambleBoard(int[NUM_ROWS][NUM_COLS]);				// depends upon slideTile()
bool isBoardSolved(int[NUM_ROWS][NUM_COLS]);		// indicates if the board is in the SOLVED state
//bool isSolvable(int[NUM_ROWS][NUM_COLS]);

													// DEVELOPMENT EXTRAS
void printTheRainbow();								// A little reminder on how to do color with the Windows API.


int main() {
	// Declarations
	HANDLE currentConsole;
	currentConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int slidingBoard[NUM_ROWS][NUM_COLS];		// the board that holds the sliding tiles
	char keyStroke = ' ';						// holds the user's keystrokes as they come in
	int directionCode = UNSET;					// used to build a direction code to be sent to slideTile()

	InitializeBoard(slidingBoard);				// initializes the board
	PrintBoard(slidingBoard, currentConsole);					// prints the board
	
	cout << endl;
	cout << "Press any key to start!" << endl; //start prompt
	_getch();

	scrambleBoard(slidingBoard); // scrambles the board
	//isSolvable(slidingBoard); //checks to see if scambled board is solvable
	system("cls"); // clears screen
	PrintBoard(slidingBoard, currentConsole); //prints new board

	//while (isSolvable == false) { //if board is unsolvable is rescrambles
	//	scrambleBoard(slidingBoard);
	//	isSolvable(slidingBoard);
	//}

	while (isBoardSolved(slidingBoard) == false) { // while board is unsolved continue game
		cout << endl << "what direction would you like to move?: " << endl;
		cin >> directionCode;

		system("cls"); //clears the screen

												// Seed the Pseudo-Random Number Generator (system clock)
		slideTile(slidingBoard, directionCode);
		PrintBoard(slidingBoard, currentConsole);
												// Driver Logic
												// 1.) This is the part where you show the board, get the moves, process the moves, and re-draw
												//  the board each time something changes.  This is the core logic of the simulation and
												//  none of the problem specific calculations should take place in main().  Instead,
												//  main() should consist of a series of controlled calls to your functions that
												//  orchestrate the top-level behavior of the simulation.

	}
	
	system("cls"); //clears the screen
	PrintBoard(slidingBoard, currentConsole); // prints the solved board
	cout << "congrats you win!";
	_getch();											// Exit
	return 0;
}

void InitializeBoard(int theBoard[NUM_ROWS][NUM_COLS]) {
	// YOUR IMPLEMENTATION GOES HERE...
	int counter = 1; 

	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			if (counter == NUM_ROWS * NUM_COLS) { 
				theBoard[i][j] = PIVOT_SYMBOL; // at the last space print the pivot symbol
			}
			else {
				theBoard[i][j] = counter++;
			}
		}
	}
}

void PrintBoard(int theBoard[NUM_ROWS][NUM_COLS], HANDLE CurrentConsole) {
	// YOUR IMPLEMENTATION GOES HERE...
	int counter = 1; // used to teast is the pieces are in the right space

	for (int i = 0; i < NUM_ROWS; i++) {
		cout << endl;
		for (int j = 0; j < NUM_COLS; j++) {
			if (theBoard[i][j] == counter) {
				SetConsoleTextAttribute(CurrentConsole, COLOR_GREEN); // if number is in the right space make it green
			}
			else {
				SetConsoleTextAttribute(CurrentConsole, COLOR_RED); // else make it red
			}
			cout << setw(3) <<theBoard[i][j]; // prints the board
			counter++;
		}
	}
}

bool slideTile(int theBoard[NUM_ROWS][NUM_COLS], int slideDirection) {
	// YOUR IMPLEMENTATION GOES HERE...
	int temp = 0;
	int emptyRow = 0;
	int emptyCol = 0;

	//find the position of the slider
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			if (theBoard[i][j] == PIVOT_SYMBOL) {
				emptyRow = i;
				emptyCol = j;

			}
		}
	}
	switch (slideDirection) {
	case SLIDE_UP: { // function for moving up
		if (emptyRow - 1 < NULL) {// if move up is OOB flag as a bad move
			slideDirection = false;
		}
		if (slideDirection != false) { // if move is good make it
			theBoard[emptyRow][emptyCol] = theBoard[emptyRow - 1][emptyCol];
			theBoard[emptyRow - 1][emptyCol] = PIVOT_SYMBOL;
		}
		else { //if not don't
			//do nothing
		}
		break;
	}

	case SLIDE_DOWN: { // function for moving down
		if (emptyRow + 1 >= NUM_ROWS) {// if move down is OOB flag as a bad move
			slideDirection = false;
		}
		if (slideDirection != false) {// if move is good make it
			theBoard[emptyRow][emptyCol] = theBoard[emptyRow + 1][emptyCol];
			theBoard[emptyRow + 1][emptyCol] = PIVOT_SYMBOL;
		}
		else {// if not don't
			//do nothing
		}
		break;
	}

	case SLIDE_RIGHT: { // function for moving right
		if (emptyCol + 1 >= NUM_COLS) {// if move right is OOB flag as a bad move
			slideDirection = false;
		}
		if (slideDirection != false) {// if move is good make it
			theBoard[emptyRow][emptyCol] = theBoard[emptyRow][emptyCol + 1];
			theBoard[emptyRow][emptyCol + 1] = PIVOT_SYMBOL;
		}
		else {// if not don't
			//do nothing
		}
		break;
	}

	case SLIDE_LEFT: { // function for moving left
		if (emptyCol - 1 < NULL) {// if move left is OOB flag as a bad move
			slideDirection = false;
		}
		if (slideDirection != false) {// if move is good make it
			theBoard[emptyRow][emptyCol] = theBoard[emptyRow][emptyCol - 1];
			theBoard[emptyRow][emptyCol - 1] = PIVOT_SYMBOL;
		}
		else {// if not don't
			//do nothing
		}
		break;
	}
	}
	return false;
}

void scrambleBoard(int theBoard[NUM_ROWS][NUM_COLS]) {
	// YOUR IMPLEMENTATION GOES HERE...
	srand((unsigned)time(NULL));
	int move;

		for (int i = 0; i < 100000; i++) //Series of random moves
		{
			move = rand() % 8 + 1;
			slideTile(theBoard, move);
		}
}

bool isBoardSolved(int amISolved[NUM_ROWS][NUM_COLS]) {
	// YOUR IMPLEMENTATION GOES HERE...
	bool solved = false;
	int counter = 1;

	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			
			if (amISolved[i][j] == counter) { // if the piece is in the right spot solved = true
				solved = true;
			}
			else if (counter == (NUM_ROWS * NUM_COLS) && amISolved[NUM_ROWS][NUM_COLS] == 0 && solved == true) { // if all pieces are in the right spot and the last spot is the pivot symbol you win
				solved = true;
			}
			else { // else the board is not solved
				solved = false;
			}
			counter++;
		}
	}
	return solved;
}

//bool isSolvable(int board[NUM_ROWS][NUM_COLS]) {
//	const int num = NUM_ROWS * NUM_COLS;
//	int arr[num];
//
//	for (int i = 0; i < NUM_ROWS; i++) {
//		for (int j = 0; j < NUM_COLS; j++) {
//			arr[i * NUM_COLS + j] = board[i][j];
//		}
//	}
//
//	int inv_count = 0;
//	for (int i = 0; i < NUM_ROWS * NUM_COLS - 1; i++)
//	{
//		for (int j = i + 1; j < NUM_ROWS * NUM_COLS; j++)
//		{
//			// count pairs(i, j) such that i appears 
//			// before j, but i > j. 
//			if (arr[j] && arr[i] && arr[i] > arr[j])
//				inv_count++;
//		}
//	}
//
//	if (inv_count % 2 == 0) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
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

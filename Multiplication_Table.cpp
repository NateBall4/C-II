#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;

#define INVALID 0

int main() {
	// We will demonstrate the dynamic nature of these arrays by prodiving
	// the rectangular dimensions through variables.
	int height = 5;
	int width = 0;

	cout << "please enter a width [1,10]: ";
	cin >> width;
	cout << endl;

	if (width > 10 || width < 0) {
		width = INVALID;
	}

	while (width == INVALID) {
		cout << "Invalid input!" << endl;
		cout << "please enter a width [1,10]: ";
		cin >> width;
		cout << endl;
		if (width > 10 || width < 0) {
			width = INVALID;
		}
	}
	// Create the root double pointer for the 2D array.
	int** ppRootPointer = NULL;

	// Allocate an array of int* variables and attach to the double pointer.
	ppRootPointer = new(int*[height]);
	
	// Allocate arrays of int variables and attach each array to one of the
	// pointers in ppRootPointer's array of pointers.
	for(int i = 0; i <= height; i++) {
		ppRootPointer[i] = new(int[width]);
	}

	// Fill the array with a count.
	for(int i = 0; i <= height; i++) {
		for(int j = 0; j <= width; j++) {
			ppRootPointer[i][j] = i * j; 
		}
		
	}

	// Print the array (full array notation).
	cout << left;
	cout << setw(3) << " ";

	//prints the numbers above the columns
	for (int i = 1; i <= width; i++) {
		cout << " " << setw(3) << i;
	}
	cout << endl;
	//seperates the column numbers from the table
	cout << setw(3) << " ";
	for (int i = 1; i <= width; i++) {
		cout << setw(4) << "---+";
	}
	cout << endl;

	//prints the table
	for (int i = 0; i < height; i++) {
		cout << setw(3) << i + 1 << ':';
		for (int j = 0; j < width; j++) {
			cout << setw(3) << ppRootPointer[i + 1][j + 1] << ':';
		}
		cout << endl;
	}

	_getch();
	return 0;
	}

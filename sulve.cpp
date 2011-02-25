/*
 * sulve.cpp
 *
 *  Created on: Feb 23, 2011
 *      Author: meiskam (meiskam@gmail.com)
 *   Copyright: All rights reserved, do not edit, do not redistribute.  Subject to change without notice.
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>
#include "sulve.h"
#include "ConsoleColor.h"
using namespace std;


int main( int argc, const char* argv[] )
{
	//cout << RAND_MAX << endl;

	srand(time(NULL)); // initiate rand

	SudokuGrid* grid = new SudokuGrid(9); // must be 9

	if (argc>2 || (argc==2 && (strlen(argv[1])!=81))) {
		cout << "\nUsage: " << argv[0] << " [puzzle]\n\n\t"
				<< "puzzle - string of 81 alnum (0-9 or .)\n";
		exit(0);
	}
	if (argc==2) {
		for (int i=0; i<81; i++) { //49-57 == 1-9 .. shift 48 (ascii digits to int)
			if (argv[1][i] >= 49 && argv[1][i] <= 57) {
				grid->at(i%9,i/9)->mValue = argv[1][i] - 48;
				grid->at(i%9,i/9)->mLocked = 1;
			}
		}
	}

	_doit(grid);
	_display(grid);

}

int _rand(int top) {
	return (rand() % top)+1;
}

void _fakegen(SudokuGrid* grid) {
	int L = grid->mSize;
	for (int j=0; j<L; j++) {
		for (int i=0; i<L; i++) {
			grid->at(i,j)->set(_rand());
			if (_rand(3)==1) {
				grid->at(i,j)->mLocked = 1;
			}
		}
	}
}

void _display(SudokuGrid* grid) {
	int L = grid->mSize;
	int m = L/3;
	//system("cls");
	cout << white << endl;
	for (int j=0; j<L; j++) {
		cout << "  ";
		for (int i=0; i<L; i++) {
			if (grid->at(i,j)->mLocked) {
				cout << green << grid->at(i,j)->mValue << white;
			}
			else if (grid->at(i,j)->mValue == 0) {
				cout << " ";
			}
			else {
				cout << grid->at(i,j)->mValue;
			}
			cout << " ";
			if ((i%m==m-1) && (i!=L-1)) cout << "| ";
		}
		if ((j%m==m-1) && (j!=L-1)) {
			cout << endl << "  ------+-------+------" << endl;
		}
		else {
			cout << endl;
		}
	}

}

void _doit(SudokuGrid* grid) {
	//HANDLE hstdin  = GetStdHandle( STD_INPUT_HANDLE  ); //temporary delay

	int j=0;
	int i=0;
	int Ri=0;
	int Rj=0;
	int L=grid->mSize;
	int m = L/3;
	list<int> temp;
	list<int>::iterator it;
	int forward = 1;
	while (j<L) {
		i=0;
		while (i<L) {
			if (grid->at(i,j)->mLocked) {
				if (forward) {
					i++;
				}
				else i--;
			}
			else {
				if (forward) {
					temp.clear();
					grid->at(i,j)->mAvail.clear();
					for (int k=1; k<=L; k++) {
						grid->at(i,j)->mAvail.push_back(k);
					}

					Ri = i/m*m; // which region in the i direction
					Rj = j/m*m; // which region in the j direction
					for (int k=0; k<L; k++) {
						temp.push_back(grid->at(k,j)->mValue); //row
						temp.push_back(grid->at(i,k)->mValue); //column
						temp.push_back(grid->at(Ri+k%m,Rj+k/m)->mValue); //region
					}
					temp.sort(); //so apparently we have to sort it, before removing dupes
					temp.unique(); //delete all dupes
					temp.remove(0);

					for (it=temp.begin(); it!=temp.end(); it++) {
						grid->at(i,j)->mAvail.remove(*it); //remove temps from avail list
					}
				}
				if (grid->at(i,j)->mAvail.size() == 0) { //if none are avail, reset, then go back a cell
					grid->at(i,j)->mValue = 0;
					grid->at(i,j)->mAvail.empty();
					i--;
					forward=0;
				}
				else {
					int ran = _rand( grid->at(i,j)->mAvail.size() );
					it=grid->at(i,j)->mAvail.begin();
					for (int k = 1; k<ran; k++) {it++;}
					grid->at(i,j)->set(*it); //set the cell value to a random avail, and move on
					i++;
					forward=1;
				}
				//temporary delay start
				//_display(grid);
				//temporary delay end
			}
			if (i<0) { j--; i=L-1; } // move up a row, if we need to, while going backwards
			if (j<0) { cout<<"ERROR: no solution found\n"; exit(42); }
		}
		j++;
	}
}

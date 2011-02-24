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

	_grid* grid = new _grid(9); // must be 9

	//_fakegen(grid);
	_doit(grid);
	_display(grid);

	/*
	_cell grid[L][L];
	_fakegen(grid);
	_display(grid);
	*/
}

int _rand(int top) {
	return (rand() % top)+1;
}

void _fakegen(_grid* grid) {
	int L = grid->size;
	for (int j=0; j<L; j++) {
		for (int i=0; i<L; i++) {
			grid->at(i,j)->set(_rand());
			if (_rand(3)==1) {
				grid->at(i,j)->locked = 1;
			}
		}
	}
}

void _display(_grid* grid) {
	int L = grid->size;
	int m = L/3;
	system("cls");
	cout << white << endl;
	for (int j=0; j<L; j++) {
		cout << "  ";
		for (int i=0; i<L; i++) {
			if (grid->at(i,j)->locked) cout << green << grid->at(i,j)->value << white;
			else cout << grid->at(i,j)->value;
			if (i%m==m-1) cout << "  ";
		}
		cout << endl;
		if (j%m==m-1) cout << endl;
	}

}

void _doit(_grid* grid) {
	int j=0;
	int i=0;
	int Ri=0;
	int Rj=0;
	int L=grid->size;
	int m = L/3;
	list<int> temp;
	list<int>::iterator it;
	int forward = 1;
	while (j<L) {
		i=0;
		while (i<L) {
			if (grid->at(i,j)->locked) {
				if (forward) i++;
				else i--;
			}
			else {
				if (forward) {
					temp.clear();
					grid->at(i,j)->avail.clear();
					for (int k=1; k<=L; k++) grid->at(i,j)->avail.push_back(k);

					Ri = i/m*m; // which region in the i direction
					Rj = j/m*m; // which region in the j direction
					int a,b,c;
					for (int k=0; k<L; k++) {
					//	grid->at(i,j)->avail.remove()
						a=grid->at(k,j)->value;
						b=grid->at(i,k)->value;
						c=grid->at(Ri+k%m,Rj+k/m)->value;
						temp.push_back(a); //row
						temp.push_back(b); //column
						temp.push_back(c); //region
					}
					temp.sort(); //so apparently we have to sort it, before removing dupes
					temp.unique(); //delete all dupes
					temp.remove(0);

					for (it=temp.begin(); it!=temp.end(); it++)
						grid->at(i,j)->avail.remove(*it); //remove temps from avail list
				}
				if (grid->at(i,j)->avail.size() == 0) { //if none are avail, reset, then go back a cell
					grid->at(i,j)->value = 0;
					grid->at(i,j)->avail.empty();
					i--;
					forward=0;
				}
				else {
					int ran = _rand( grid->at(i,j)->avail.size() );
					it=grid->at(i,j)->avail.begin();
					for (int k = 1; k<ran; k++) {it++;}
					grid->at(i,j)->set(*it); //set the cell value to a random avail, and move on
					i++;
					forward=1;
				}
			}
			if (i<0) { j--; i=L-1; } // move up a row, if we need to, while going backwards
			if (j<0) { cout<<"ERROR: j<0\n"; exit(42); }
		}
		j++;
	}
}

/*

char* _avail(_cell grid[L][L]) {
	return 0;
}
*/

/*
 * sulve.cpp
 *
 *  Created on: Feb 23, 2011
 *      Author: meiskam (meiskam@gmail.com)
 *   Copyright: All rights reserved, do not edit, do not redistribute.  Subject to change without notice.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include "sulve.h"

int main( int argc, const char* argv[] )
{
	srand(time(NULL)); // initiate rand

	_cell grid[L][L];
	_fakegen(grid);
	_display(grid);
}

void _display(_cell grid[L][L]) {
	system("cls");
	printf("\n");
	for (char j=0; j<L; j++) {
		printf("  ");
		for (char i=0; i<L; i++) {
			printf("%i", grid[i][j].value);
			if (i%3==2) printf("  ");
		}
		printf("\n");
		if (j%3==2) printf("\n");
	}

}

char _rand(char top) {
	return rand() % top;
}

void _fakegen(_cell grid[L][L]) {
	for (char j=0; j<L; j++) {
		for (char i=0; i<L; i++) {
			grid[i][j].value = _rand();
		}
	}
}

void _generate(_cell grid[L][L]) {
	char j=0;
	char i=0;
	while (j<L) {
		i=0;
		while (i<L) {
			if (grid[i][j].avail.empty()) {
				for (int k=0; k<L; k++) grid[i][j].avail.push_back(k);
				grid[i][j].value = -1;
			}


			if (i<0) { j--; i=L-1; }
			else { i++; }
		}
		j++;
	}
}

char* _avail(_cell grid[L][L]) {
	return 0;
}

/*
 * sulve.h
 *
 *  Created on: Feb 23, 2011
 *      Author: meiskam (meiskam@gmail.com)
 *   Copyright: All rights reserved, do not edit, do not redistribute.  Subject to change without notice.
 */

#ifndef SULVE_H_
#define SULVE_H_

#include <list>
using namespace std;

class SudokuCell {
	public:
		int mValue;
		int mLocked;
		list<int> mAvail;
		SudokuCell() { mValue = 0; mLocked = 0; };
		void set(int a) { mValue = a; mAvail.remove(a); };
};

class SudokuGrid {
	public:
		int mSize;
		vector<vector<SudokuCell> > values;
		SudokuGrid(int size) {
			mSize = size;
			values.resize(mSize);
			for (int i=0; i<mSize; i++) values.at(i).resize(mSize);
		}
		SudokuCell* at(int i, int j) {
			return &(values.at(i).at(j));
		}
};

int _rand(int);
int _rand() { return _rand(9); };
void _display(SudokuGrid*);
void _fakegen(SudokuGrid*);
void _doit(SudokuGrid*);

#endif /* SULVE_H_ */

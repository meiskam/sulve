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

class _cell {
	public:
		int value;
		int locked;
		list<int> avail;
		_cell() { value = 0; locked = 0; };
		void set(int a) { value = a; avail.remove(a); };
};

class _grid {
	public:
		int size;
		vector<vector<_cell> > values;
		_grid(int a) {
			size = a;
			values.resize(size);
			for (int i=0; i<size; i++) values.at(i).resize(size);
		}
		_cell* at(int i, int j) {
			return &(values.at(i).at(j));
		}
};

int _rand(int);
int _rand() { return _rand(9); };
void _display(_grid*);
void _fakegen(_grid*);
void _doit(_grid*);

#endif /* SULVE_H_ */

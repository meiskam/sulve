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

class _cell {
	public:
		char value;
		char locked;
		std::list<char> failed;
		std::list<char> avail;
		_cell() { value = -1; locked = 0; };
		void set(char a) { value = a; failed.push_back(a); };
		//_cell(char a, char b) { value = a; locked = b; };
		//_cell(char a) { _cell(a, 0); };
		//_cell() { _cell(-1, 0); };
		//~_cell() { delete failed; };

};

char const L = 9;
void _display(_cell[L][L]);
void _fakegen(_cell[L][L]);
char _rand(char);
char _rand() { return _rand(10); };

#endif /* SULVE_H_ */

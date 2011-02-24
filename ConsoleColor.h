/*
 * ConsoleColor.h
 *
 *  Created on: Nov 17, 2006
 *    Copyleft: Vincent Godin
 *
 * Modified on: Nov 26, 2008
 *          By: Dzuka Automat
 *
 *      Source: http://www.codeproject.com/KB/cpp/cout_color.aspx
 */

#ifndef CONSOLECOLOR_H_
#define CONSOLECOLOR_H_

#include <iostream>
#include <windows.h>


enum color
{
red=FOREGROUND_RED|FOREGROUND_INTENSITY,
green=FOREGROUND_GREEN|FOREGROUND_INTENSITY,
blue=FOREGROUND_BLUE|FOREGROUND_INTENSITY,
yellow=FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY,
white=FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE
};

inline std::ostream& operator<< (std::ostream& s,const color& c)
{
HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hStdout,c);
return s;
}

#endif /* CONSOLECOLOR_H_ */

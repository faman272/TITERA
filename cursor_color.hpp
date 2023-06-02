#ifndef CURSOR_COLOR_HPP
#define CURSOR_COLOR_HPP

#include <windows.h>

using namespace std;

/**
 * Function to change the console color.
 * 
 * @param color The color code to set the console to.
 */

void changeConsoleColor(int color) //function to change console color
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // get standar handle to reference cursor
    SetConsoleTextAttribute(console, color); //set changes
}

void hideCursor() // function to hide cursor
{
    HANDLE cursor = GetStdHandle(STD_OUTPUT_HANDLE); // get standar handle to reference cursor
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1; //size default cursor set to 1%
    info.bVisible = FALSE; //set visible to false
    SetConsoleCursorInfo(cursor, &info); //set changes
}

#endif
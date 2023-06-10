#ifndef READ_FILE_HPP
#define READ_FILE_HPP

#include "cursor_and_color.hpp"
#include <iostream>
#include <fstream>


/**
 * Function to create a new file or edit an existing file.
 * 
 * @param filename The name of the file to read.
 */

void readFile(const string &filename){
    hideCursor();
    system("cls");
    ifstream file(filename); // open file to read
    if (!file.is_open())
    {
        cout << "\n\033[31mFile not found or file name incorrect.\n";
        cout << "\n\033[34mPress Enter to return.....\033[37m";
        cin.ignore();
        cin.ignore();  // wait for enter
        system("cls"); // clear layar
        return;
    }
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    
    cout << "\033[33m" << filename << "\033[37m"
         << " | \033[31mRead Only Mode\033[37m | \033[36mPress enter to return\033[37m \n______________________________________________________\n"; // header

    // display text with the line number
    int colorIndex = 0;
    int colors[] = {FOREGROUND_GREEN, FOREGROUND_BLUE, FOREGROUND_RED, FOREGROUND_RED | FOREGROUND_GREEN};
    int lineCount = 1;
    string fileExt = filename.substr(filename.find_last_of(".") + 1);
    changeConsoleColor(15); //default color white
    cout << lineCount << " "; 
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ' || text[i] == '\n') //white space and newline
        {
            if (fileExt != "txt")
            {
                changeConsoleColor(colors[colorIndex]);
                colorIndex = (colorIndex + 1) % 4; // change console each new word
            }
            if (text[i] == '\n')
            {
                lineCount++;
                cout << text[i];
                changeConsoleColor(15);
                cout << lineCount << " ";
                if (fileExt != "txt")
                {
                    changeConsoleColor(colors[colorIndex]);
                }

                
            }  
            else
            {
                cout << text[i];
            }
        }
        else
        {
            cout << text[i];
        }
    }

    cin.ignore();
    cin.ignore();  
    system("cls"); // clear screen
}

#endif

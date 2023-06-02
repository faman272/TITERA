#ifndef CREATE_FILE_HPP
#define CREATE_FILE_HPP

#include "cursor_color.hpp"
#include <iostream>
#include <fstream>
#include <conio.h>

/**
 * Function to create a new file or edit an existing file.
 * 
 * @param filename The name of the file to be created.
 */

void createFile(const string &filename)
{
    hideCursor();
    // cek apakah file sudah ada
    ifstream existingFile(filename);
    if (existingFile.is_open())
    {
        cout << "\nFile " << "\033[33m" << filename << " \033[31malready exist." << "\033[37m" << endl;
        cin.ignore();
        cin.ignore();  // wait for enter
        system("cls"); // clear screen
        return;
    }

    string text; //variabel string to store text
    bool saved = true;
    string save;
    int cursorPos = text.length(); // current cursor position
    string fileExt = filename.substr(filename.find_last_of(".") + 1); //variable text to store file extension
    
    do
    {
        system("cls"); // clear screen
        // display header
        if (saved)
        {
            save = " | \033[32mFile Saved";
        }
        else
        {
            save = " | \033[36mFile Unsaved";
        }
        changeConsoleColor(15);
        cout << "\033[33m" << filename << "\033[37m"
             << " | Press \033[31m~\033[37m to Save file, \033[31m`\033[37m to Run File and \033[31mEsc\033[37m to Exit" << save 
             << "\n\033[37m_____________________________________________________________________________\n";

        // display text with cursor
        int colorIndex = 0;
        int colors[] = {FOREGROUND_GREEN, FOREGROUND_RED | FOREGROUND_BLUE, FOREGROUND_BLUE, FOREGROUND_RED | FOREGROUND_GREEN}; //array untuk menyimpan warna
        int lineCount = 1;
        changeConsoleColor(15);
        cout << lineCount << " ";
        if (fileExt != "txt")
        {
            changeConsoleColor(colors[colorIndex]);
            colorIndex = (colorIndex + 1) % 4;
        }
        for (int i = 0; i < text.length(); i++)
        {
            if (i == cursorPos)
            {
                changeConsoleColor(15);
                cout << "|"; // display cursor
            }
            if (text[i] == ' ' || text[i] == '\n')
            {
                if (fileExt != "txt")
                {
                    changeConsoleColor(colors[colorIndex]);
                    colorIndex = (colorIndex + 1) % 4; // change color for each new word
                }
                
                if (text[i] == '\n')
                {
                    lineCount++;
                    cout << text[i];
                    changeConsoleColor(15); //line number set to default color
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
        if (cursorPos == text.length())
        {
            changeConsoleColor(15);
            cout << "|"; // display cursor at end of text
        }   

        char key = _getch(); // get input

        if (key == 8) // backspace key
        {
            if (cursorPos > 0)
            {
                text.erase(cursorPos - 1, 1); // delete character before cursor
                cursorPos--;
                saved = false;
            }
        }
        else if (key == -32)
        {                             // if arrow key is pressed
            char arrowKey = _getch(); // get second character
            switch (arrowKey)
            {
            case 75: // left arrow key
                if (cursorPos > 0)
                    cursorPos--; // move cursor to the left
                break;
            case 77: // right arrow key
                if (cursorPos < text.length())
                    cursorPos++; // move cursor to the right
                break;
            }
        }
        else if (key == '~')
        { // ~ to save file
            ofstream file(filename);
            file << text;
            file.close();
            saved = true;
        }
        else if (key == 13) //enter key
        {
            text.insert(cursorPos, 1, '\n'); // insert new line at cursor position
            cursorPos++;
            saved = false;
        }
        else if (key == 27) //Esc key
        {
            if (!saved)
            {
                cout << "\n\n\033[31mFile not saved. Are you sure you want to exit? (Y/N) ";
                char choice = getch();
                if (choice == 'Y' || choice == 'y')
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        else if (key == '`')
        {
            system("cls");
            ofstream file(filename);
            file << text;
            file.close();
            string command = "g++ " + filename + " -o " + filename.substr(0, filename.find_last_of(".")) + " && " + filename.substr(0, filename.find_last_of("."));
            int result = system(command.c_str());
            cin.ignore();
            cin.ignore();
        }

        else
        {
            text.insert(cursorPos, 1, key);
            cursorPos++;
            saved = false;
        }
    } while (true);
}

#endif
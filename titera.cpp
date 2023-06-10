/*
*   Copyright (C) 2023-* TITERA GROUP, Inc.
*
*
*   This program was developed by Group 2 as part of a mini project for the Object Oriented Programming subject
*   at the University of North Sumatra, specifically designed to function as a text editor.
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the MIT License 
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

/*
Group members :
1. Fathurrahman (221402098)
2. William Benadectus (221402136)
3. Alexander Brema Pindonta Sitepu(221402085)
4. Gerald Salomo Pasaribu(221402139)
5. Muhammad Dzikrie Zaini(221402116)
*/

#include "create_file.hpp" //function to create file    [->Fathurrahman]
#include "read_file.hpp"  //function to read file       [->William]
#include "edit_file.hpp" //function to edit file        [->Gerald]
#include "delete_file.hpp" //function to delete file    [->Alexander]

#include <iostream>

using namespace std;

class TextEditor
{
private:
    string choic;
    bool exitProgram = false; // flag to track if the program should exit

public:                                  
    void textEditorMenu();              
};

void TextEditor::textEditorMenu() //function menu  [->Dzikrie]
{
    hideCursor();
    while (!exitProgram)
    {
        system("cls"); // clear screen
        cout << "\033[33m";
        cout << "\t\t\t\t\t\t\t  TITERA - Titik Terang Editor" << endl;
        cout << "\033[36m";
        cout << "\t\t\t\t\t\t\t\t    Versi 1.0.1\n"
             << endl;
        cout << "\033[37m";
        cout << "Enter \033[35mc\033[37m to Create, \033[35mr\033[37m to Read, \033[35me\033[37m to Update, \033[35md\033[37m to Delete, and \033[35mq\033[37m to Exit: ";
        char choice;
        cin >> choice;

        switch (choice)
        {
            case 'c':
                cout << "Enter the file name, don't forget to include the file extension: ";
                cin >> choic;
                createFile(choic);
                break;
            case 'e':
                cout << "Enter the file name, don't forget to include the file extension: ";
                cin >> choic;
                editFile(choic);
                break;
            case 'r':
                cout << "Enter the file name, don't forget to include the file extension: ";
                cin >> choic;
                readFile(choic);
                break;
            case 'd':
                cout << "Enter the file name, don't forget to include the file extension: ";
                cin >> choic;
                deleteFile(choic);
                cin.ignore();
                cin.ignore(); // wait for enter
                break;
            case 'q':
                exitProgram = true; // set the flag to exit the program
                break;
            default:
                system("cls");
                cout << "\n\033[31mInvalid input. Please try again.\033[37m" << endl;
                cin.ignore();
                cin.ignore(); // wait enter key
        }
    }
}

int main()
{
    TextEditor teks;
    teks.textEditorMenu();
    return 0;
}

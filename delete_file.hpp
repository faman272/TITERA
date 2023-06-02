#ifndef DELETE_FILE_HPP
#define DELETE_FILE_HPP


#include "cursor_color.hpp"
#include <iostream>
#include <fstream>

/**
 * Function to create a new file or edit an existing file.
 * 
 * @param filename The name of the file to be deleted.
 */


void deleteFile(const string &filename)
{
    hideCursor();

    // Check if the file exists
    ifstream file(filename);
    if (!file)
    {
        cout << "\033[31m";
        cout << "\nFailed to delete the file, make sure the filename and extension are correct!" << endl
             << endl;
        cout << "\033[37m"
             << "Press enter to return....." << endl;
        cin.ignore();
        cin.ignore();
        return;
    }
    file.close();

    // Prompt the user to confirm before deleting the file
    cout << "\n\033[37mAre you sure to delete " 
         << "\033[33m" 
         << filename << " \033[37mfile? (\033[32my\033[37m/\033[31mn\033[37m): ";
    char choice;
    cin >> choice;
    if (choice != 'y' && choice != 'Y')
    {
        cout << "\nFile deletion canceled." << endl;
        cout << "\033[37m"
             << "\nPress enter to return....." << endl;
        cin.ignore();
        cin.ignore();
        return;
    }

    // Delete the file
    if (remove(filename.c_str()) != 0)
    {
        cout << "\033[31m";
        cout << "\nFailed to delete the file, make sure the filename and extension are correct!" << endl
             << endl;
        cout << "\033[37m"
             << "Press enter to return....." << endl;
    }
    else
    {
        cout << "\nFile "
             << "\033[33m" << filename << "\033[32m"
             << " Successfully Deleted!" << endl
             << endl;
        cout << "\033[37m"
             << "Press enter to return....." << endl;
    }
}


#endif
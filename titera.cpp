
/*
Group members :
1. Fathurrahman (221402098)
2. William Benadectus (221402136)
3. Alexander Brema Pindonta Sitepu(221402085)
4. Gerald Salomo Pasaribu(221402139)
5. Muhammad Dzikrie Zaini(221402116)
*/

#include <iostream>
#include <fstream>
#include <conio.h> 
#include <windows.h>

using namespace std;

class TextEditor
{
public:
    void hideCursor(); // fungsi untuk menyembunyikan kursor bawaan windows  [->Fathurrahman]
    void changeConsoleColor(int color);//                                    [->Fathurrahman]
    void createFile(const string &filename); // function to create file      [->Fathurrahman]
    void editFile(const string &filename);   // function to edit file        [->William]
    void readFile(const string &filename);   // function to read file        [->Dzikrie]
    void deleteFile(const string &filename); // function to delete file      [->Gerald]
    void textEditorMenu(); // function to display menu                       [->Alexander]                 
};

/**
 * Fungsi untuk mengubah warna teks di konsol.
 * @param color Warna teks yang diinginkan (dalam format kode warna Windows).
 */

void TextEditor::changeConsoleColor(int color) //function to change console color
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // get standar handle to reference cursor
    SetConsoleTextAttribute(console, color); //set changes
}

void TextEditor::hideCursor() // function to hide cursor
{
    HANDLE cursor = GetStdHandle(STD_OUTPUT_HANDLE); // get standar handle to reference cursor
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1; //size default cursor set to 1%
    info.bVisible = FALSE; //set visible to false
    SetConsoleCursorInfo(cursor, &info); //set changes
}

void TextEditor::createFile(const string &filename)
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

void TextEditor::readFile(const string &filename)
{

    system("cls");
    hideCursor();            // hide cursor terminal
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

void TextEditor::editFile(const string &filename)
{
    hideCursor();
    system("cls");
    ifstream existingFile(filename);
    if (!existingFile.is_open())
    {
        cout << "\n\033[31mFile not found or file name incorrect.\n";
        cout << "\n\033[32mPress Enter to return.....\033[37m";
        cin.ignore();
        cin.ignore(); 
        system("cls"); // clear screen
        return;
    }
    string text((istreambuf_iterator<char>(existingFile)), istreambuf_iterator<char>());
    bool saved = true;
    string save; 
    int cursorPos = text.length(); // current cursor position di akhir text
    string fileExt = filename.substr(filename.find_last_of(".") + 1); 
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
             << " | Press \033[31m~\033[37m to Save file, \033[31m`\033[37m to Run File dan \033[31mEsc\033[37m to Exit" 
             << save 
            << "\n\033[37m_____________________________________________________________________________\n";

        // display text with cursor
        int colorIndex = 0;
        int colors[] = {FOREGROUND_GREEN, FOREGROUND_BLUE, FOREGROUND_RED, FOREGROUND_RED | FOREGROUND_GREEN};
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
        if (cursorPos == text.length())
        {
            changeConsoleColor(15);
            cout << "|"; // display cursor at end of text
        }

        char key = _getch(); // get input
        if (key == 8)
        { // backspace key
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
        else if (key == 13) //enter
        {
            text.insert(cursorPos, 1, '\n'); // insert new line at cursor position
            cursorPos++;
            saved = false;
        }
        else if (key == 27) //escape
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

void TextEditor::deleteFile(const string &filename)
{
    hideCursor();

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

void TextEditor::textEditorMenu()
{
    hideCursor();
    string choic;
    bool exitProgram = false; // flag to track if the program should exit
    while (!exitProgram)
    {
        system("cls"); // clear screen
        cout << "\033[33m";
        cout << "\t\t\t\t\t\t\t  TITERA - Titik Terang Editor" << endl;
        cout << "\033[36m";
        cout << "\t\t\t\t\t\t\t\t    Versi 1.0.\n"
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

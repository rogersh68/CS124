/***********************************************************************
* Program:
*    Sudoku
* Author:
*    Hannah Rogers
* Summary: 
*    This program will open a sudoku file and show options. It will allow
*    the user to see the options, display the board, edit the board,
*    see the possible values, enforce the rules, write the board to a new
*    file and close the game.
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define SIZE 9

bool readFile(char fileName[], int board[][SIZE]);
void writeBoard(int board[][SIZE]);
void interact(int board[][SIZE]);
void displayBoard(int board[][SIZE]);
void editSquare(int board[][SIZE], string coordinates);
string getCoordinates();
bool computeValues(int board[][SIZE], string coordinates, bool possible[]);
void displayPossible(int board[][SIZE], string coordinates);

/**********************************************************************
 * MAIN: will get the fileName and call the functions.
 ***********************************************************************/
int main()
{
   //declare variables
   char fileName[256];
   int board[SIZE][SIZE];

   //get the file name
   cout << "Where is your board located? ";
   cin  >> fileName;

   //call functions
   readFile(fileName, board);
   if (readFile(fileName, board) == false)
      return 0;
   interact(board);
   writeBoard(board);
   
   return 0;
}

/**********************************************************************
 * READFILE: will read in file to board array.
 **********************************************************************/
bool readFile(char fileName[], int board[][SIZE])
{
   //open the file
   ifstream fin(fileName);
   if (fin.fail())
   {
      cout << "Unable to open file " << fileName << endl;
      return false;
   }

   //read the file into the array
   for (int row = 0; row < SIZE; row++)
      for (int col = 0; col < SIZE; col++)
         fin >> board[row][col];

   //close the file
   fin.close();

   return true;
}

/**********************************************************************
 * WRITEBOARD: will write the board to a new file.
 **********************************************************************/
void writeBoard(int board[][SIZE])
{
   //declare variables
   char destinationFile[256];

   //prompt for destination filename
   cout << "What file would you like to write your board to: ";
   cin  >> destinationFile;

   //open the destination file
   ofstream fout(destinationFile);
   if (fout.fail())
      cout << "Error opening destination file";

   //write board array into file
   for (int row = 0; row < SIZE; row++)
   {
      for (int col = 0; col < SIZE; col++)
      {
         fout << board[row][col] << " ";
      }
      fout << "\n";
   }

   //close the file
   fout.close();

   //indicate file has written
   if (fout.fail())
      cout << "Error writing file\n";
   else
      cout << "Board written successfully\n";
}
   
/*********************************************************************
 * INTERACT: will display options and take users input.
 *********************************************************************/
void interact(int board[][SIZE])
{
   //declare variables
   char option;
   string coordinates;

   //show options and board
   cout << "Options:\n";
   cout << "   ?  Show these instructions\n";
   cout << "   D  Display the board\n";
   cout << "   E  Edit one square\n";
   cout << "   S  Show the possible values for a square\n";
   cout << "   Q  Save and Quit\n\n";

   displayBoard(board);

   //accept and execute options
   do
   {
      //accept user option
      cout << "\n> ";
      cin  >> option;

      switch (toupper(option))
      {
         case '?':
            //display options
            cout << "Options:\n";
            cout << "   ?  Show these instructions\n";
            cout << "   D  Display the board\n";
            cout << "   E  Edit one square\n";
            cout << "   S  Show the possible values for a square\n";
            cout << "   Q  Save and Quit\n\n";
            break;
         case 'D':
            //display the board
            displayBoard(board);
            break;
         case 'E':
            //get coordinates, and edit the square
            coordinates = getCoordinates();
            editSquare(board, coordinates);
            break;
         case 'S':
            //get coordinates, get and show possible values
            coordinates = getCoordinates();
            displayPossible(board, coordinates);
            break;
         case 'Q':
            //quit the loop
            break;
         default:
            //indicate user error
            cout << "Enter a valid option: ";
      }
   }
   while (toupper(option) != 'Q');
}

/************************************************************************
 * DISPLAYBOARD: will display the sudoku board.
 ************************************************************************/
void displayBoard(int board[][SIZE])
{
   //display the board column letters
   cout << "   A B C D E F G H I\n";

   //display board and fill in numbers
   for (int row = 0; row < SIZE; row++)
   {
      cout << row + 1 << "  ";
      for (int col = 0; col < SIZE; col++)
      {
         //change 0's to spaces
         if (board[row][col] == 0)
            cout << " ";
         else
            cout << board[row][col];
         
         //set up board squares
         if (col == 2 || col == 5)
            cout << "|";
         else if (col == 8)
            cout << endl;
         else
            cout << " ";
      }
      if (row == 2 || row == 5)
         cout << "   -----+-----+-----\n";
   }
}

/***********************************************************************
 * GETCOORDINATES: will get coordinates from the user.
 ***********************************************************************/
string getCoordinates()
{
   //declare variables
   string coordinates;

   //get coordinates
   cout << "What are the coordinates of the square: ";
   cin >> coordinates;

   //return coordinates
   return coordinates;
}

/***********************************************************************
 * EDITSQUARE: will allow user to add value to sudoku square if valid.
 ***********************************************************************/
void editSquare(int board[][SIZE], string coordinates)
{
   //declare variables
   int input;
   char userCol = toupper(coordinates[0]);
   char userRow = coordinates[1];
   int col = int(userCol) - 65;
   int row = int(coordinates[1]) - 49;
   bool validAnswers[SIZE];

   //determine if square is filled, if empty accept valid input
   if (board[row][col] != 0)
      cout << "ERROR: Square '" << userCol << userRow << "' is filled\n";
   else
   {
      cout << "What is the value at '" << userCol << userRow << "': ";
      cin  >> input;
   
      //validate answer
      validAnswers[SIZE] = computeValues(board, coordinates, validAnswers); 

      //give error message if input is not valid
      if (validAnswers[input - 1] == false)
      {
         cout << "ERROR: Value '" << input << "' in square '"
              << userCol << userRow << "' is invalid\n";
      }
      else
         //insert user input into board
         board[row][col] = input;
   }
}

/***********************************************************************
 * COMPUTEVALUES: will compute the possible values for the coordinates.
 ***********************************************************************/
bool computeValues(int board[][SIZE], string coordinates, bool possible[])
{
   //declare variables
   char userCol = toupper(coordinates[0]);
   char userRow = coordinates[1];
   int col = int(userCol) - 65;
   int row = int(coordinates[1]) - 49;
   
   //set initial values to true
   for (int i = 0; i < SIZE; i++)
      possible[i] = true;

   //set false values in row
   for (int r = 0; r < SIZE; r++)
   {
      if (board[r][col] != 0)
         possible[board[r][col] - 1] = false;
   }

   //set false values in  column
   for (int c = 0; c < SIZE; c++)
   {
      if (board[row][c] != 0)
         possible[board[row][c] - 1] = false;
   }

   //set false values in 3x3 square
   for (int iRow = 0; iRow < 3; iRow++)
   {
      for (int iCol = 0; iCol < 3; iCol++)
      {
         if (board[row / 3 * 3 + iRow][col / 3 * 3 + iCol] != 0)
            possible[board[row / 3 * 3 + iRow]
                     [col / 3 * 3 + iCol] - 1] = false;
      }
   }        

   return possible[SIZE];
}

/**********************************************************************
 * DISPLAYPOSSIBLE: will display the possible values of a square.
 **********************************************************************/
void displayPossible(int board[][SIZE], string coordinates)
{
   //declare variables
   bool possible[SIZE];
   char userCol = toupper(coordinates[0]);
   char userRow = coordinates[1];
   bool first = true;
   
   //call computeValues
   possible[SIZE] = computeValues(board, coordinates, possible);

   //display comma separated values
   cout << "The possible values for '" << userCol << userRow
        << "' are: ";
   
   for (int i = 0; i < SIZE; i++)
   {
      if (possible[i] == true)
      {
         //no comma before first value
         if (first == true)
         {
            cout << i + 1;
            first = false;
         }
         //add comma before values
         else
            cout << ", " << i + 1;
      }
   }

   cout << endl;
}

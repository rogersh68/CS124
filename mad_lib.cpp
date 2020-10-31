/***********************************************************************
* Program:
*    Mad Lib
* Author:
*    Hannah Rogers
* Summary: 
*    This program will read a Mad Lib from a user's specified file and
*    then ask the user to answer the questions.It will display the Mad
*    Lib and ask if they wish to play again.
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

void readFile();
void askQuestion(char story[]);
void display(char story[][32], int i);

/***********************************************************************
 * READFILE: will read a file and find the questions.
 ***********************************************************************/
void readFile()
{
   //get file
   char fileName[256];

   cout << "Please enter the filename of the Mad Lib: ";
   cin  >> fileName;

   ifstream fin(fileName);

   if (fin.fail())
   {
      cout << "unable to open file "
           << fileName << endl;
   }

   //declare variables
   char story[256][32];
   int i = 0;

   cin.ignore();

   while (i < 256 && fin >> story[i])
   {
      //ask questions
      askQuestion(story[i]);
      i++;
   }

   //close file
   fin.close();

   //send to display function
   display(story, i);

   return;
}


/***********************************************************************
 * ASKQUESTION: will convert the questions to readable text and prompt.
 ***********************************************************************/
void askQuestion(char story[])
{
   if (story[0] != ':' || !isalpha(story[1]))
      return;

   //prompt for word
   cout << "\t" << (char)toupper(story[1]);

   for (char *p = story + 2; *p; p++)
      cout << (*p == '_' ? ' ' : (char)tolower(*p));

   cout << ": ";

   //get user's words
   cin.getline(story, 32);

   return;
}


/***********************************************************************
 * DISPLAY: will display the story with proper punctuation.
 ***********************************************************************/
void display(char story[][32], int i)
{
   cout << endl;

   for (int x = 0; x < i; x++)
   {
      //change tokens to punctuation
      if (story[x][0] == ':' && story[x][1] == '!')
      {
         story[x][0] = '\n';
         story[x][1] = '\0';
      }
      else if (story[x][0] == ':' && story[x][1] == '<')
      {
         story[x][0] = '<';
         story[x][1] = '\0';
      }
      else if (story[x][0] == ':' && story[x][1] == '>')
      {
         story[x][0] = '>';
         story[x][1] = '\0';
      }
      else if (story[x][0] == ':' && story[x][1] == '.')
      {
         story[x][0] = '.';
         story[x][1] = '\0';
      }
      else if (story[x][0] == ':' && story[x][1] == ',')
      {
         story[x][0] = ',';
         story[x][1] = '\0';
      }

      //add spaces
      if ((isalpha(story[x][0]) && isalpha(story[x + 1][0]))
          || (story[x][0] == '.' && isalpha(story[x + 1][0]))
          || (story[x][0] == ',' && isalpha(story[x + 1][0])))
         cout << story[x] << ' ';
      else if (story[x][0] == '"')
         cout << ' ' << story[x] << ' ';
      else if (story[x][0] == '<' && story[x - 1][0] != '\n')
         cout << " \"";
      else if (story[x][0] == '<')
         cout << '"';
      else if (story[x][0] == '>' && isalpha(story[x + 1][0]))
         cout << "\" ";
      else if (story[x][0] == '>')
         cout << '"';
      else
         cout << story[x];
   }

   cout << endl;

   return;
}

/***********************************************************************
 * MAIN: will call functions and allow user to continue playing.
 ***********************************************************************/
int main()
{
   //declare variable
   char playAgain = 'y';

   //let user play as many times as they want
   while (playAgain != 'n' || playAgain != 'N')
   {
      if (playAgain == 'y' || playAgain == 'Y')
      {
         readFile();
         cout << "Do you want to play again (y/n)? ";
         cin  >> playAgain;
      }
      else if (playAgain == 'n' || playAgain == 'N')
      {
         cout << "Thank you for playing.\n";
         break;
      }
      else
      {
         cout << "Invalid entry. Do you want to play again (y/n)? ";
         cin  >> playAgain;
      }
   }

   return 0;
}

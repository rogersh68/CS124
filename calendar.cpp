/***********************************************************************
* Program:
*    Calendar
* Author:
*    Hannah Rogers
* Summary: 
*    This program will take a user input of month and year and will 
*    display the calendar table for that specific month and year.
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

/***********************************************************************
 *GETMONTH: will prompt the user for the month number.
 **********************************************************************/
int getMonth()
{
   int month;

   do
   {
      cout << "Enter a month number: ";
      cin  >> month;

      if (month > 12 || month < 1)
         cout << "Month must be between 1 and 12.\n";
   }
   while (month > 12 || month < 1);

   return month;
}


/**********************************************************************
 *GETYEAR: will prompt the user for the year.
 *********************************************************************/
int getYear()
{
   int year;

   do
   {
      cout << "Enter year: ";
      cin  >> year;

      if (year < 1753)
         cout << "Year must be 1753 or later.\n";
   }
   while (year < 1753);

   return year;
}


/**********************************************************************
 *ISLEAPYEAR: will determine if the input year is a leap year.
 *********************************************************************/
bool isLeapYear(int year)
{
   if (year % 4 != 0)
      return false;
   else if (year % 100 == 0)
      return true;
   else if (year % 400 == 0)
      return false;
   else
      return true;
}


/**********************************************************************
 *NUMDAYSINYEAR: will calculate the number of days in a year.
 *********************************************************************/
int numDaysInYear(int year)
{
   if (isLeapYear(year))
      return 366;
   else
      return 365;
}


/*********************************************************************
 *NUMDAYSINMONTH: will determine the number of days in a month.
 ********************************************************************/
int numDaysInMonth(int month, int year)
{
   if (month == 1)
      return 31;
   else if (month == 2)
   {
      if (isLeapYear(year))
         return 29;
      else
         return 28;
   }
   else if (month == 3)
      return 31;
   else if (month == 4)
      return 30;
   else if (month == 5)
      return 31;
   else if (month == 6)
      return 30;
   else if (month == 7)
      return 31;
   else if (month == 8)
      return 31;
   else if (month == 9)
      return 30;
   else if (month == 10)
      return 31;
   else if (month == 11)
      return 30;
   else
      return 31;
}


/**********************************************************************
 *COMPUTEOFFSET:
 ********************************************************************/
int computeOffset (int month, int year)
{
   int count = 0;

   for (int countYear = 1753; countYear < year; countYear++)
   {
      count += numDaysInYear(countYear);
   }

   for (int countMonth = 1; countMonth < month ; countMonth++)
   {
      count += numDaysInMonth(countMonth, year);
   }

   return count % 7;
}


/**********************************************************************
 *DISPLAYHEADER: will display the month and year at the top.
 *********************************************************************/
void displayHeader(int month, int year)
{
   if (month == 1)
      cout << "\nJanuary";
   else if (month == 2)
      cout << "\nFebruary";
   else if (month == 3)
      cout << "\nMarch";
   else if (month == 4)
      cout << "\nApril";
   else if (month == 5)
      cout << "\nMay";
   else if (month == 6)
      cout << "\nJune";
   else if (month == 7)
      cout << "\nJuly";
   else if (month == 8)
      cout << "\nAugust";
   else if (month == 9)
      cout << "\nSeptember";
   else if (month == 10)
      cout << "\nOctober";
   else if (month == 11)
      cout << "\nNovember";
   else
      cout << "\nDecember";

   cout << ", " << year << endl;
}

/**********************************************************************
 *DISPLAYTABLE: will display the calendar days as a table.
 ********************************************************************/
void displayTable(int numDays, int offset)
{
   int count;

   //heading                                                                    
   cout << "  Su  Mo  Tu  We  Th  Fr  Sa\n";

   //set the offset spacing                                                     
   if (offset == 0)
      cout << setw(4) << " ";
   else if (offset == 1)
      cout << setw(8) << " ";
   else if (offset == 2)
      cout << setw(12) << " ";
   else if (offset == 3)
      cout << setw(16) << " ";
   else if (offset == 4)
      cout << setw(20) << " ";
   else if (offset == 5)
      cout << setw(24) << " ";
   else
      cout << setw(4);

   //count the number of days                                                   
   for (count = 1; count <= numDays; count ++)
   {
      cout << setw(4) << count;

   //add a new line for the end of the week                                     
   if ((offset + count + 1) % 7 == 0)
      cout << endl;
   }

   //conditional new line
   if ((offset + count) % 7 != 0)
      cout << endl;
 
   return;
}

/**********************************************************************
 *DISPLAY: will call the displayHeader and displayTable functions.
 *********************************************************************/
void display(int month, int year, int offset)
{
   int numDays = numDaysInMonth(month, year);
   displayHeader(month, year);
   displayTable(numDays, offset);
}   

/**********************************************************************
 * MAIN: will call all of the functions.
 ***********************************************************************/
int main()
{
   int month = getMonth();
   int year = getYear();
   int offset = computeOffset(month, year);

   display(month, year, offset);

   return 0;
}

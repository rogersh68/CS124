/***********************************************************************
* Program:
*    Monthly Budget
* Author:
*    Hannah Rogers
* Summary:
*    This program will take the user's monthly income and expenditures
*    and will display a budget report.
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

/**********************************************************************
 * GETINCOME FUNCTION: will get income from the user and return it.
 *********************************************************************/
double getIncome()
{
   double  monthlyIncome;
   cout << "\tYour monthly income: ";
   cin >> monthlyIncome;
   return monthlyIncome;
}

/*********************************************************************
 * GETBUDGETLIVING FUNCTION: will get budgeted living from user and
 * return it.
 *********************************************************************/
double getBudgetLiving()
{
   double budgetedLiving;
   cout << "\tYour budgeted living expenses: ";
   cin >> budgetedLiving;
   return budgetedLiving;
}

/*********************************************************************
 * GETACTUALLIVING FUNCTION: will get actual living from user and
 * return it.
 *********************************************************************/
double getActualLiving()
{
   double actualLiving;
   cout << "\tYour actual living expenses: ";
   cin >> actualLiving;
   return actualLiving;
}

/**********************************************************************
 * GETACTUALTAX FUNCTION: will get actual tax from user and return it.
 *********************************************************************/
double getActualTax()
{
   double actualTax;
   cout << "\tYour actual taxes withheld: ";
   cin >> actualTax;
   return actualTax;
}

/**********************************************************************
 * GETACTUALTITHING FUNCTION: will get actual tithing from user and
 * return it.
 *********************************************************************/
double getActualTithing()
{
   double actualTithing;
   cout << "\tYour actual tithe offerings: ";
   cin >> actualTithing;
   return actualTithing;
}

/*********************************************************************
 * GETACTUALOTHER FUNCTION: will get actual other from user and
 * return it.
 ********************************************************************/
double getActualOther()
{
   double actualOther;
   cout << "\tYour actual other expenses: ";
   cin >> actualOther;
   return actualOther;
}

/*********************************************************************
 * COMPUTETAX FUNCTION: will compute tax and return it.
 *********************************************************************/
double computeTax(double &monthlyIncome)
{
   double yearlyIncome = monthlyIncome * 12;
   double yearlyTax;
      
   if (yearlyIncome >= 336550)
      yearlyTax = 91043 + 0.35 * (yearlyIncome - 336550);
   else if (yearlyIncome >= 188450)
      yearlyTax = 42170 + 0.33 * (yearlyIncome - 188450);
   else if (yearlyIncome >= 123700)
      yearlyTax = 24040 + 0.28 * (yearlyIncome - 123700);
   else if (yearlyIncome >= 61300)
      yearlyTax = 8440 + 0.25 * (yearlyIncome - 61300);
   else if (yearlyIncome >= 15100)
      yearlyTax = 1510 + 0.15 * (yearlyIncome - 15100);
   else
      yearlyTax = yearlyIncome * 0.10;
      
   return yearlyTax / 12;
}

/*********************************************************************
 * COMPUTETITHING FUNCTION: will compute tithing and return it.
 *********************************************************************/
double computeTithing(double &monthlyIncome)
{
   double incomeTithe = monthlyIncome;
   return incomeTithe * .10;
}

/**********************************************************************
 * DISPLAY FUNCTION: will compute some budgets and difference as well
 * as display the budget breakdown.
 **********************************************************************/
void display(double &monthlyIncome, double &budgetLiving,
             double &actualTax,double &actualTithing,
             double &actualLiving, double &actualOther)
{
   //declare variables
   double income =  monthlyIncome;
   double bLiving = budgetLiving;
   double aTax = actualTax;
   double aTithe = actualTithing;
   double aLiving = actualLiving;
   double aOther = actualOther;
   double budgetTax = computeTax(income);
   double budgetTithing = computeTithing(income);
   double budgetOther = (monthlyIncome - budgetTax - budgetTithing
                         - budgetLiving);
   double actualDifference = (monthlyIncome - actualTax - actualTithing
                              - actualLiving - actualOther);
   double budgetDifference = 0.00;

   //display breakdown
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
  
   cout << "The following is a report on your monthly expenses\n";

   cout << "\tItem                  Budget          Actual\n";

   cout << "\t=============== =============== ===============\n";

   cout << "\tIncome          $"
        << setw(11) << monthlyIncome
        << "    $"
        << setw(11) << monthlyIncome << endl;

   cout << "\tTaxes           $"
        << setw(11) << budgetTax
        << "    $"
        << setw(11) << actualTax << endl;

   cout << "\tTithing         $"
        << setw(11) << budgetTithing
        << "    $"
        << setw(11) << actualTithing << endl;
   cout << "\tLiving          $"
        << setw(11) << budgetLiving
        << "    $"
        << setw(11) << actualLiving << endl;

   cout << "\tOther           $"
        << setw(11) << budgetOther
        << "    $"
        << setw(11) << actualOther << endl;

   cout << "\t=============== =============== ===============\n";

   cout << "\tDifference      $"
        << setw(11) << budgetDifference
        << "    $"
        << setw (11) << actualDifference << endl;

   return;
}


/***********************************************************************
 * MAIN FUNCTION: will display the first greeting/prompt and then call
 * all of the functions to create the budget.
 ***********************************************************************/
int main()
{
   cout << "This program keeps track of your monthly budget\n"
        << "Please enter the following:\n";
   double monthlyIncome =  getIncome();
   double budgetLiving =  getBudgetLiving();
   double actualLiving = getActualLiving();
   double actualTax = getActualTax();
   double actualTithing = getActualTithing();
   double actualOther = getActualOther();

   cout << endl;

   display(monthlyIncome, budgetLiving, actualTax,
           actualTithing, actualLiving, actualOther);
   
   return 0;
}

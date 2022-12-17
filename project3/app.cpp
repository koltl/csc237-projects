/***************************************************************
Author:         Kolt Litrenta 
Filename:       app.cpp 
Course:         CSC 237 Data Structures
Assignment:     Project 3
Date            November 11, 2021
Purpose:        Creates the TermList pointer (ThePoly), invokes
                the proper read in, printing, and evalulation
                inherited subclass functions for the respective
                data structures.  This is achieved by either
                existing command line arguments or by manual
                instruction guided by the appropiate menus 
***************************************************************/

/*!
*   \file app.cpp
*   \brief Program that handles both batch and interative mode.  Also creates the TermList pointer and invokes proper functions
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "TermList.h"
#include "TermArrayList.h"
#include "TermVectorList.h"
#include "TermDblLinkList.h"

using namespace std;

/*!
    *   displayMenu
    *   \brief Display a list of containers available to use
    *   \return none
*/
void displayMenu();

/*!
    *   arrayMenu
    *   \brief Display a list of print functions to use with an evalulation option
    *   \param filename The file name to pass onto the array's read-in function
    *   \param ThePoly The TermList pointer be instantiated with the selected data type
    *   \return none
*/
void arrayMenu(const string &filename, TermList *ThePoly);

/*!
    *   vectorMenu
    *   \brief Display a list of print functions to use with an evalulation option
    *   \param filename The file name to pass onto the vectors's read-in function
    *   \param ThePoly The TermList pointer be instantiated with the selected data type
    *   \return none
*/
void vectorMenu(const string &filename, TermList *ThePoly);

/*!
    *   dbllinkMenu
    *   \brief Display a list of print functions to use with an evalulation option
    *   \param filename The file name to pass onto the doubly linked list's read-in function
    *   \param ThePoly The TermList pointer be instantiated with the selected data type
    *   \return none
*/
void dbllinkMenu(const string &filename, TermList *ThePoly);

/*!
    *   evaluate
    *   \brief Evaluate the TermList ThePoly after asking user for x value
    *   \param ThePoly The TermList pointer which is used to call the appropiate overloaded operator for a selected data type
    *   \return none
*/
void evaluate(TermList *ThePoly);

/*!
    *   printEverything
    *   \brief If program is ran using batch mode (command line arguments), then go through all list container print and evaluation methods
    *   \param filename The file name to pass into each container's read-in function
    *   \param ThePoly The TermList pointer used to be instantiated with each data type
    *   \param evalX The user provided x value to calculate P(x) as captured via command line argument
    *   \return none
*/
void printEverything(const string &filename, TermList *ThePoly, double evalX);

int main(int argc, char *argv[]) {
    // declare pointer of ThePoly of TermList
    TermList *ThePoly;

    // if additional arguments are present, run through following block
    if (argc > 1) {

        // create fstream file object to read in from file for batchmode
        fstream file;
        
        // store evalulation number from argument 3 to evalX
        double evalX = atof(argv[2]);

        // open file with filename provided from argument 2
        file.open(argv[1]);

        // if the file fails to open or evalulation number is incomplete, 
        // skip print everything and move onto menu
        if (file.fail() || !evalX) {
            cout << "Command line arguments incomplete!  Skipping...\n";
        } else {

            // close the file
            file.close();

            // store filename from argument 2 to fileName
            string fileName(argv[1]);

            // invoke function to print everything
            printEverything(fileName, ThePoly, evalX);
            return 0;
        }
    }

    // declare string filename and char selection
    string filename;
    char selection;

    
    // create fstream file object to read in from file
    fstream file;

    do {
        cout << "Please enter filename: ";

        // retreive filename from user input and attempt to open
        cin >> filename;
        file.open(filename);

        // if failed, inform user and repeat
        if (file.fail()) {
            cout << "Error opening file, please try again!\n";
        }
    } while (file.fail());

    while (true) {
        
        // display main menu options
        displayMenu();

        // take in user selection
        cin >> selection;

        switch (selection) {
            case '1':
                arrayMenu(filename, ThePoly);
                break;
            case '2':
                vectorMenu(filename, ThePoly);
                break;
            case '3':
                dbllinkMenu(filename, ThePoly);
                break;
            case '4':
                return 0;
            default:
                cout << "\nInput not recognized, please try again\n";
        }
    }
}

void printEverything (const string &filename, TermList *ThePoly, double evalX) {
    /*********************************************************************
	*   Function name:  printEverything
	*   Description:  calls each read in, iterative print, pointer print (if applicable), and evaulation
                      function for ThePoly of TermArrayList, TermVectorList, and TermDblLinkList
	*   Parameters: const string &filename - filename to use for each respective readIntoList function,
                    TermList *ThePoly - Term list pointer to use for each subclass,
                    double evalX - Number to use for each polynomial evaluation within a data structure
	*                                                                   
	*   Return Value: none
	*********************************************************************/
    ThePoly = new TermArrayList;
    ThePoly->readIntoList(filename);
    ThePoly->printIteratively();
    cout << "Evaluated: P(" << evalX << ")=" << (*ThePoly)(evalX) << endl << endl;
    ThePoly->printPtr();
    cout << "Evaluated: P(" << evalX << ")=" << (*ThePoly)(evalX) << endl << endl;
    ThePoly->printRecursively();
    cout << "Evaluated: P(" << evalX << ")=" << (*ThePoly)(evalX) << endl << endl;

    ThePoly = new TermVectorList;
    ThePoly->readIntoList(filename);
    ThePoly->printIteratively();
    cout << "Evaluated: P(" << evalX << ")=" << (*ThePoly)(evalX) << endl << endl;
    ThePoly->printRecursively();
    cout << "Evaluated: P(" << evalX << ")=" << (*ThePoly)(evalX) << endl << endl;

    ThePoly = new TermDblLinkList;
    ThePoly->readIntoList(filename);
    ThePoly->printIteratively();
    cout << "Evaluated: P(" << evalX << ")=" << (*ThePoly)(evalX) << endl << endl;
    ThePoly->printRecursively();
    cout << "Evaluated: P(" << evalX << ")=" << (*ThePoly)(evalX) << endl << endl;
}

void displayMenu() {
    /*********************************************************************
	*   Function name:  displayMenu
	*   Description:  displays main menu of each possible term list type to choose from
	*   Parameters: none
	*                                                                   
	*   Return Value: none
	*********************************************************************/
    cout << "\nSelect Term List Type ?\n";
    cout << "1. Object Array\n";
    cout << "2. Vector\n";
    cout << "3. Doubly Linked List\n";
    cout << "4. Exit\n";
}

void arrayMenu(const string &filename, TermList* ThePoly) {
    /*********************************************************************
	*   Function name:  arrayMenu
	*   Description:  displays object array submenu options and invokes the appropiate member function based from user selection
	*   Parameters: const string &filename - filename to use for the data structure's readIntoList function
                    TermList* ThePoly - Term list pointer ThePoly to be instantiated with the TermArrayList
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // instantiate ThePoly with new TermArrayList and invoke its read in function using the filename parameter
    ThePoly = new TermArrayList;
    ThePoly->readIntoList(filename);

    char selection;
    do {
        // display submenu selection for array list
        cout << "\nSelect Action ?\n";
        cout << "------------------------------------------------\n";
        cout << "Object C++ Array\n";
        cout << "------------------------------------------------\n";
        cout << "1. Object Array Iterative Print\n";
        cout << "2. Object Array Pointer Print\n";
        cout << "3. Object Array Recursive Print\n";
        cout << "4. Evaluate the Polynomial\n";
        cout << "5. Exit Object Array\n";

        // read user input and invoke the appropiate function followed by an evaluation
        cin >> selection;
        switch (selection) {
            case '1':
                ThePoly->printIteratively();
                evaluate(ThePoly);
                break;
            case '2':
                ThePoly->printPtr();
                evaluate(ThePoly);
                break;
            case '3':
                ThePoly->printRecursively();
                evaluate(ThePoly);
                break;
            case '4':
                evaluate(ThePoly);
                break;
            case '5':
                // exit the submenu and return to the main menu
                return;
            default:
                cout << "\nInput not recognized, please try again\n";
        }
    } while (selection != 4);
}

void vectorMenu(const string &filename, TermList* ThePoly) {
    /*********************************************************************
	*   Function name:  vectorMenu
	*   Description:  displays vector list submenu options and invokes the appropiate member function based from user selection
	*   Parameters: const string &filename - filename to use for the data structure's readIntoList function
                    TermList* ThePoly - Term list pointer ThePoly to be instantiated with the TermVectorList
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // instantiate ThePoly with new TermVectorList and invoke its read in function using the filename parameter
    ThePoly = new TermVectorList;
    ThePoly->readIntoList(filename);

    char selection;
    do {
        // display submenu selection for vector list
        cout << "\nSelect Action ?\n";
        cout << "------------------------------------------------\n";
        cout << "Vector\n";
        cout << "------------------------------------------------\n";
        cout << "1. Vector Iterative Print\n";
        cout << "2. Vector Recursive Print\n";
        cout << "3. Evaluate the Polynomial\n";
        cout << "4. Exit Vector\n";

        // read user input and invoke the appropiate function followed by an evaluation
        cin >> selection;
        switch (selection) {
            case '1':
                ThePoly->printIteratively();
                evaluate(ThePoly);
                break;
            case '2':
                ThePoly->printRecursively();
                evaluate(ThePoly);
                break;
            case '3':
                evaluate(ThePoly);
                break;
            case '4':
                // exit the submenu and return to the main menu
                return;
            default:
                cout << "\nInput not recognized, please try again\n";
        }
    } while (selection != 4);
}

void dbllinkMenu(const string &filename, TermList* ThePoly) {
    /*********************************************************************
	*   Function name:  dbllinkMenu
	*   Description:  displays doubly linked list submenu options and invokes the appropiate member function based from user selection
	*   Parameters: const string &filename - filename to use for the data structure's readIntoList function
                    TermList* ThePoly - Term list pointer ThePoly to be instantiated with the TermDblLinkList
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // instantiate ThePoly with new TermDblLinkList and invoke its read in function using the filename parameter
    ThePoly = new TermDblLinkList;
    ThePoly->readIntoList(filename);

    char selection;
    do {
        // display submenu selection for doubly linked list
        cout << "\nSelect Action ?\n";
        cout << "------------------------------------------------\n";
        cout << "Doubly Linked List\n";
        cout << "------------------------------------------------\n";
        cout << "1. Doubly Linked List Iterative Print\n";
        cout << "2. Doubly Linked List Recursive Print\n";
        cout << "3. Evaluate the Polynomial\n";
        cout << "4. Exit Doubly Linked List\n";

        // read user input and invoke the appropiate function followed by an evaluation
        cin >> selection;
        switch (selection) {
            case '1':
                ThePoly->printIteratively();
                evaluate(ThePoly);
                break;
            case '2':
                ThePoly->printRecursively();
                evaluate(ThePoly);
                break;
            case '3':
                evaluate(ThePoly);
                break;
            case '4':
                // exit the submenu and return to the main menu
                return;
            default:
                cout << "\nInput not recognized, please try again\n";
        }
    } while (selection != 4);
}

void evaluate(TermList *ThePoly) {
    /*********************************************************************
	*   Function name:  evaluate
	*   Description:  prompts the user to input a number to evaluate the polynomial and display the result
	*   Parameters: TermList* ThePoly - Term list pointer ThePoly to be used for evaluation of the polynomial
                    double x - the number to evaluate the polynomial with if passed
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    double x;

    // ask user for number to use for evaluation
    cout << "Enter a value x for P(x) >";
    cin >> x;

    // print the evaluate result
    cout << "Evaluated: P(" << x << ")=" << (*ThePoly)(x) << endl;
}
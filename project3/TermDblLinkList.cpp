/***************************************************************
Author:         Kolt Litrenta 
Filename:       TermDblLinkList.cpp  
Course:         CSC 237 Data Structures
Assignment:     Project 3
Date            November 11, 2021
Purpose:        Function implementations for the TermDblLinkList
                subclass, inherited from the TermList class
***************************************************************/

/*!
*   \author Kolt Litrenta
*   \file TermDblLinkList.cpp
*   \brief Function implementations for the TermDblLinkList subclass, inherited from the TermList class
*/

#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include "TermDblLinkList.h"

using namespace std;
using namespace std::chrono;

// Doubly linked list constructor
TermDblLinkList::TermDblLinkList() {}

void TermDblLinkList::readIntoList(string filename) {
    /*********************************************************************
	*   Function name:  readIntoList
	*   Description:  reads terms from file and inserts them into doubly linked list
	*   Parameters: string filename - the name of the file to read terms from
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // start timer to time read in function
    auto begin = high_resolution_clock::now();

    ifstream source(filename.c_str());

    // create doubly linked iterator used for comparing exponents
    DblLinkItr<Term> ListIt(ThePoly);

    // declare coefficient and exponent for temporary storage used for term creation (or combination)
    double coefficient;
    int exponent;

    // delcare boolean matchFound as false
    bool matchFound = false;

    // loop if there are incoming coefficient and exponent values
    while (source >> coefficient >> exponent) {
        
        // start the doubly linked list iterator at head
        ListIt.start();

        // check if the doubly linked list is populated
        if (!ListIt.isEmpty()) {
            do {

                // check current node's exponent against incoming exponent
                if (ListIt().getExponent() == exponent) {

                    // if there is a match, set matchFound to true
                    matchFound = true;

                    // create new object with the combined coefficients and same exponent
                    Term temp(ListIt().getCoefficient()+coefficient, exponent);

                    // remove matching term by exponent
                    ThePoly.remove(ListIt());

                    // insert new term of combined coefficients
                    ThePoly.insert(temp);
                    break;
                }
                // progress the iterator until it reaches the last node
            } while (!ListIt++.isLastNode());
        }
        


        // if match has not been found, continue with insertion.  Otherwise, reset matchFound
        if (!matchFound) {
            ThePoly.insert(Term(coefficient, exponent));
        } else {
            matchFound = false;
        }
    }

    // rewind file back to beginning for other read in functions 
    source.close();
    source.clear();

    // end timer to time read in function
    auto end = high_resolution_clock::now();

    // calculate the difference from between end and begin timings which is casted in microseconds
    auto ticks = duration_cast<microseconds>(end-begin);

    // indicate the amount of time the read in function has taken to complete
    cout << "\n\nTermDblLinkList read function took " << ticks.count() << " microseconds to complete\n\n";
}

void TermDblLinkList::printIteratively() {
    /*********************************************************************
	*   Function name:  printIteratively
	*   Description:  print doubly linked list iteratively in descending order
	*   Parameters: none
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // indicate the following print method
    cout<<"---------------------------------"<<endl;
    cout<<"|Doubly Linked List Iterative   |"<<endl;
    cout<<"---------------------------------"<<endl;

    // start timer to time iterative print function
    auto begin = high_resolution_clock::now();

    // create doubly linked list iterator used for progressing through and printing out doubly linked list
    DblLinkItr<Term> ListIt(ThePoly);

    // start iterator at start (head) node of doubly linked list, move up through list until it reaches the end (tail) node
    for (ListIt.start(); !ListIt.isLastNode(); ++ListIt) {

        // print out unique term followed by a +
        cout << ListIt() << " + ";
    }

    // since loop stops at the last node, print the remaining last node
    cout << ListIt() << " ";
    cout << endl << endl;

    // end timer once iterative print finishes
    auto end = high_resolution_clock::now();

    // calculate the difference from between end and begin timings which is casted in microseconds
    auto ticks = duration_cast<microseconds>(end-begin);

    // indicate the amount of time the iterative print has taken to complete
    cout << "\nThis took " << ticks.count() << " microseconds to run\n";
}

// called by app.cpp
void TermDblLinkList::printRecursively() {
    /*********************************************************************
	*   Function name:  printRecursively
	*   Description:  indicate that doubly linked list will be printed recursively
                      and invoke the appropiate recursive print function
	*   Parameters: none
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // indicate the following print method
    cout<<"---------------------------------"<<endl;
    cout<<"|Doubly Linked List Recursive   |"<<endl;
    cout<<"---------------------------------"<<endl;

    DblLinkItr<Term> ListIt(ThePoly);

    ListIt.start();

    // start timer to time recursive print function
    auto begin = high_resolution_clock::now();

    // call recursive print starting at the first (head) of doubly linked list
    recursivePrint(ListIt);

    // end timer once recursive print returns
    auto end = high_resolution_clock::now();
    
    // calculate the difference from between end and begin timings which is casted in microseconds
    auto ticks = duration_cast<microseconds>(end-begin);
    cout << endl << endl;

    // indicate the amount of time the recursive print has taken to complete
    cout << "\nThis took " << ticks.count() << " microseconds to run\n";
}

void TermDblLinkList::recursivePrint(DblLinkItr<Term> ListIt) {
    /*********************************************************************
	*   Function name:  recursivePrint
	*   Description:  print doubly linked list recursively in descending order
	*   Parameters: ListIt - doubly linked list iterator used for printing
                             current term and passing its incremented value
                             to recursive print call
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // print current term of doubly linked list
    cout << ListIt();

    // if the current node the iterator is pointing is the last node, return
    if (ListIt.isLastNode()) {
        return;
    }

    // print '+'
    cout << " + ";

    // call the function againing passing the preincremented list iterator for recursion
    recursivePrint(++ListIt);
}

double TermDblLinkList::operator()(double x) const {
    /*********************************************************************
	*   Function name:  operator()
	*   Description:  operator overload () which evaluates and returns P(x) from user provided x
	*   Parameters: double x - number used to evaluate the polynomial
	*                                                                   
	*   Return Value: double result - the value from P(x)
	*********************************************************************/

    // declare the result starting from 0.0
    double result = 0.0;

    // create doubly linked list iterator used for progressing through and retreiving values term values used for evaluation
    DblLinkItr<Term> evalulate(ThePoly);

    // start iterator at start(head) node of doubly linked list, move up through list until it eaches the last (tail) node
    for (evalulate.start(); !evalulate.isLastNode(); ++evalulate) {

        // add each evaluation onto result
        result += evalulate().getCoefficient()*pow(x, evalulate().getExponent());
    }

    // since loop stops at the last node, evaluate the last term and add it onto result
    result += evalulate().getCoefficient()*pow(x, evalulate().getExponent());

    // return resulting value P(x)
    return result;
}
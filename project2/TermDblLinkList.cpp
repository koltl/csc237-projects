/***************************************************************
Author:         Kolt Litrenta 
Filename:       TermDblLinkList.cpp  
Purpose:        Function implementations for the TermDblLinkList
                subclass, inherited from the TermList class
***************************************************************/

#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "TermDblLinkList.h"

using namespace std;

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
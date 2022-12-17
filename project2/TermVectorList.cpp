/***************************************************************
Author:         Kolt Litrenta 
Filename:       TermVectorList.cpp  
Purpose:        Function implementations for the TermVectorList
                subclass, inherited from the TermList class
***************************************************************/

#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include "TermVectorList.h"

using namespace std;

// Vector list constructor
TermVectorList::TermVectorList() {}

void TermVectorList::readIntoList(string filename) {
    /*********************************************************************
	*   Function name:  readIntoList
	*   Description:  reads terms from file and inserts them into vector list
	*   Parameters: string filename - the name of the file to read terms from
	*                                                                   
	*   Return Value: none
	*********************************************************************/
    fstream source(filename.c_str());

    // declare coefficient and exponent for temporary storage used for term creation (or combination)
    double coefficient;
    int exponent;

    // declares boolean matchFound as false
    bool matchFound = false;

    // loop if there are incoming coefficient and exponent values from file
    while (source >> coefficient >> exponent) {

        // loop through all existing vector term objects
        for (int i = ThePoly.size() - 1; i >= 0; i--) {

            // check current Term element's exponent against incoming exponent
            if (ThePoly.at(i).getExponent() == exponent) {

                // if there is a match, set matchFound to true
                matchFound = true;

                // create new object with the combined coefficients and same exponent and push it to vector
                ThePoly.push_back(Term(ThePoly.at(i).getCoefficient()+coefficient, exponent));

                // erase Term element from vector where match had occured
                ThePoly.erase(ThePoly.begin() + i);
            }
        }

        // if match has not been found, continue with insertion.  Otherwise, reset matchFound
        if (!matchFound) {
            ThePoly.push_back(Term(coefficient, exponent));
        } else {
            matchFound = false;
        }
    }

    // sort vector from start to end based on Term's exponents
    sort(ThePoly.begin(), ThePoly.end());

    // rewind file back to beginning for other read in functions
    source.clear();
    source.seekg(0);
}

void TermVectorList::printIteratively() {
    /*********************************************************************
	*   Function name:  printIteratively
	*   Description:  print vector list iteratively in descending order
	*   Parameters: none
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // indicate the following print method
    cout<<"---------------------------------"<<endl;
    cout<<"|Vector Iterative               |"<<endl;
    cout<<"---------------------------------"<<endl;

    // loop through vector beginning to end using iteration
    for (int i = 0; i < ThePoly.size(); i++) {

        // if not a beginning or end, print '+' between each term
        if (i != 0 && i != ThePoly.size()) {
            cout << " + ";
        }

        // print the unique term
        cout << ThePoly[i];
    }

    cout << endl << endl;
}

double TermVectorList::operator()(double x) const {
    /*********************************************************************
	*   Function name:  operator()
	*   Description:  operator overload () which evaluates and returns P(x) from user provided x
	*   Parameters: double x - number used to evaluate the polynomial
	*                                                                   
	*   Return Value: double result - the value from P(x)
	*********************************************************************/

    // declare the result starting from 0.0
    double result = 0.0;

    // iterate through the vector beginning to end
    for (auto eval = ThePoly.begin(); eval != ThePoly.end(); eval++) {

        // add each evaluation onto result
        result += eval->getCoefficient()*(pow(x, eval->getExponent()));
    }

    // return resulting value P(x)
    return result;
}
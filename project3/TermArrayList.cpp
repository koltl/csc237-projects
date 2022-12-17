/***************************************************************
Author:         Dr. Spiegel (edited by Kolt Litrenta) 
Filename:       TermArrayList.cpp  
Course:         CSC 237 Data Structures
Assignment:     Project 3
Date            November 11, 2021
Purpose:        Function implementations for the TermArrayList
                subclass, inherited from the TermList class
***************************************************************/

/*!
*   \authors Dr. Spiegel, Kolt Litrenta
*   \file TermArrayList.cpp
*   \brief Function implementations for the TermArrayList subclass, inherited from the TermList class
*/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include "TermArrayList.h"

using namespace std;
using namespace std::chrono;

  TermArrayList::TermArrayList()
  { numTerms=0; }

  void TermArrayList::readIntoList(string filename)
  /*********************************************************************
	*   Function name:  readIntoList
	*   Description:  reads terms from file and inserts them into term array list
	*   Parameters: string filename - the name of the file to read terms from
	*                                                                   
	*   Return Value: none
	*********************************************************************/
  { // start timer to time read in function
    auto begin = high_resolution_clock::now();
    ifstream source(filename.c_str());

    // declare coefficient and exponent for temporary storage used for term creation (or combination)
    double coeff;
    int expn;

    // delcare boolean matchFound as false
    bool matchFound = false;

    // loop if there are incoming coefficient and exponent values
    while (source >> coeff >> expn)  {

      // if array list is populated, run through to find an existing exponent that matches incoming exponent
      if (numTerms > 0) {

        // iterate through all term elements of array list
        for (int x = 0; x < numTerms; x++) {

          // check current term exponent against incoming exponent
          if (ThePoly[x].getExponent() == expn) {

            // if match has been found, set it to true
            matchFound = true;

            // create temporary term object with combined coefficients and same exponent
            Term temp(ThePoly[x].getCoefficient()+coeff,expn);

            // replace element with matching term with respect to exponent to new term with combined coefficients
            ThePoly[x] = temp;
          }
        }
      }

      // if match has not been found, continue with insertion.  Otherwise, reset matchFound
      if (!matchFound) {

        // only insert a new term element if array is not full
        if (numTerms <= 9) {
          Term T(coeff,expn);
          ThePoly[numTerms++]=T;
        } else {
          cout << "\nTerm array reached maximum unique terms!  Skipping " << coeff << "x^" << expn << endl;
        }
        
      } else {
        matchFound = false;
      }
      
    }

    // sort term array in descending order by exponent
    for (int i = 0; i < numTerms; i++) {
      for (int y = i + 1; y < numTerms; y++) {
        if (ThePoly[i].getExponent() < ThePoly[y].getExponent()) {
          Term newtemp(ThePoly[i].getCoefficient(), ThePoly[i].getExponent());
          ThePoly[i] = ThePoly[y];
          ThePoly[y] = newtemp;
        }
      }
    }
    source.close();
    source.clear();

    // end timer to time read in function
    auto end = high_resolution_clock::now();

    // calculate the difference from between end and begin timings which is casted in microseconds
    auto ticks = duration_cast<microseconds>(end-begin);

    // indicate the amount of time the read in function has taken to complete
    cout << "\n\nTermArrayList read function took " << ticks.count() << " microseconds to complete\n\n";
  }

  // Print the data iteratively
  void TermArrayList::printIteratively()
  /*********************************************************************
	*   Function name:  printIteratively
	*   Description:  print term array list iteratively in descending order
	*   Parameters: none
	*                                                                   
	*   Return Value: none
	*********************************************************************/
//  void printObjectArrayIterator(TermArray ThePoly[], int numTerms)
  { // start timer to time iterative print function
    auto begin = high_resolution_clock::now();
    cout<<"---------------------------------"<<endl;
    cout<<"|Object  Array  Iterative       |"<<endl;
    cout<<"---------------------------------"<<endl;
    for(int i=0; i<numTerms; i++) {
//      cout<<" "<<ThePoly[i]<< "    " << ThePoly[i].getArea() << 
//	    		"    " << ThePoly[i].getPerimeter() << endl;
      cout <<  ThePoly[i] << (i < numTerms-1?" + ":"");
    }

    // end timer once iterative print has finished
    auto end = high_resolution_clock::now();
    cout << endl << endl;

    // calculate the difference from between end and begin timings which is casted in microseconds
    auto ticks = duration_cast<microseconds>(end-begin);

    // indicate the amount of time the iterative print has taken to complete
    cout << "\nThis took " << ticks.count() << " microseconds to run\n";
}


  // Print the data with a pointer
  void TermArrayList::printPtr()
  /*********************************************************************
	*   Function name:  printPtr
	*   Description:  print term array list in descending order using a pointer
	*   Parameters: none
	*                                                                   
	*   Return Value: none
	*********************************************************************/
  //void printObjectArrayPointerRecursive(TermArray* ThePoly, int numTerms)
  { // start timer to time pointer print function
    auto begin = high_resolution_clock::now();
    cout<<"---------------------------------"<<endl;
    cout<<"|Object  Array  Pointer         |"<<endl;
    cout<<"---------------------------------"<<endl;
    Term *now=ThePoly;
    for(int i=0; i<numTerms; i++)
      cout << "" << *(now++)  << (i < numTerms-1?" + ":"");

    // end timer once pointer print has finished
    auto end = high_resolution_clock::now();
    cout << endl << endl;

    // calculate the difference from between end and begin timings which is casted in microseconds
    auto ticks = duration_cast<microseconds>(end-begin);

    // indicate the amount of time the pointer print has taken to complete
    cout << "\nThis took " << ticks.count() << " microseconds to run\n";
  }

// called by app.cpp
  void TermArrayList::printRecursively() {
  /*********************************************************************
	*   Function name:  printRecursively
	*   Description:  indicate that array list will be printed recursively
                      and invoke the appropiate recursive print function
	*   Parameters: none
	*                                                                   
	*   Return Value: none
	*********************************************************************/
    cout<<"---------------------------------"<<endl;
    cout<<"|Object  Array  Recursive         |"<<endl;
    cout<<"---------------------------------"<<endl;

    // start timer to time recursive print function
    auto begin = high_resolution_clock::now();

    // call recursive print, passing the array list and the number of terms in the array
    recursivePrint(ThePoly, numTerms);

    // end timer once recursive print has finished
    auto end = high_resolution_clock::now();
    cout << endl << endl;

    // calculate the difference from between end and begin timings which is casted in microseconds
    auto ticks = duration_cast<microseconds>(end-begin);

    // indicate the amount of time the recursive print has taken to complete
    cout << "\nThis took " << ticks.count() << " microseconds to run\n";
  }

  void TermArrayList::recursivePrint(Term ThePoly[], int numTerms) {
  /*********************************************************************
	*   Function name:  recursivePrint
	*   Description:  print term array list in descending order using recursion
	*   Parameters: ThePoly[] - Object array to print recursively
                  numTerms - the number of terms that exist in object array
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // used to track number of prints
    static int i = 0;

    // print the current term at index i
    cout << ThePoly[i];

    // preincrement i, if it matches the number of terms, return, other '+' and continue
    if (++i == numTerms) {
      // reset i back to 0
      i = i - numTerms;
      return;
    } else {
      cout << " + ";
    }

    // call the function again passing the object array and number of terms for recursion
    recursivePrint(ThePoly, numTerms);
  }

  // Evaluate the Polynomial
  double TermArrayList::operator()(double x) const
  /*********************************************************************
	*   Function name:  operator()
	*   Description:  operator overload () which evaluates and returns P(x) from user provided x
	*   Parameters: double x - number used to evaluate the polynomial
	*                                                                   
	*   Return Value: double result - the value from P(x)
	*********************************************************************/
  { double result=0.0;
    for (int idx=0;idx<numTerms;idx++)
      result+=ThePoly[idx](x);
    return(result);
  }
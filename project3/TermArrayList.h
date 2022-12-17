/***************************************************************
Author:         Dr. Spiegel (edited by Kolt Litrenta)
Filename:       TermArrayList.h  
Course:         CSC 237 Data Structures
Assignment:     Project 3
Date            November 11, 2021
Purpose:        Header file for the TermArrayList subclass
                and function implementations
***************************************************************/

/*!
*   \authors Dr. Spiegel, Kolt Litrenta
*   \file TermArrayList.h
*   \brief Header file for the TermArrayList subclass and function implementations
*/

#ifndef WORDDATALIST_H
#define WORDDATALIST_H

#include <fstream>
#include <string>
#include "TermList.h"
#include "term.h"

using namespace std;

/*!
*   \class TermArrayList
*   \brief Subclass functions used to insert into and print from object array
*/

class TermArrayList : public TermList {
public:

  // TermArrayList constructor
  /*!
    *   \fn Constructor
    *   \param none
    *   \return none
    */
  TermArrayList();

  // Put a string of strings into the list object
  //void readIntoList(ifstream &source);
  /*!
    *   \fn readIntoList
    *   \brief reads data from a file as terms and inserts them into list array
    *   \param filename the file name to read from for term creation
    *   \return none
    */
  void readIntoList(string filename);

  // Print the data iteratively
  /*!
    *   \fn printIteratively
    *   \brief prints array list iteratively
    *   \param none
    *   \return none
    */
  void printIteratively();

  // function that initiates the recursive print
    /*!
    *   \fn printRecursively
    *   \brief initiates the recursive print
    *   \param none
    *   \return none
    */
  void printRecursively();

  // Print the data using recursion
    /*!
    *   \fn recursivePrint
    *   \brief print the data from list array using recursion
    *   \param ThePoly[] Object array to use for recursive print
    *   \param numTerms The number of elements the object array holds
    *   \return none
    */
  void recursivePrint(Term ThePoly[], int numTerms);
  
  // Print the data with a pointer
  /*!
    *   \fn printPtr
    *   \brief print the data from list array using an iterative pointer
    *   \param none
    *   \return none
    */
  void printPtr();

  // Evaluate the Polynomial
  /*!
    *   operator()
    *   \brief evaluates P(x) from user given x
    *   \param x the x value used to calculate P(x) from the array list of terms
    *   \return double the P(x) value
    */
  virtual double operator()(double x) const;

private:
  // Term object array with a size of 10
  /*!
  * Object array of Term used to store Term objects
  */
  Term ThePoly[10];

  // variables that holds the number of elements currently in the object array
  /*!
  * holds the number of elements currently in the object array
  */
  int numTerms;
  
};
  
#endif

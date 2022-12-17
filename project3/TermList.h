/***************************************************************
Author:         Dr. Spiegel (edited by Kolt Litrenta)
Filename:       TermList.h  
Course:         CSC 237 Data Structures
Assignment:     Project 3
Date            November 11, 2021
Purpose:        Header file for the functions that TermArrayList,
                TermVectorList, and TermDblLinkList will inherit
                and partly use
***************************************************************/

/*!
*   \authors Dr. Spiegel, Kolt Litrenta
*   \file TermList.h
*   \brief Header file for the functions that TermArrayList, TermVectorList, and TermDblLinkList will inherit and partly use
*/

#ifndef TERMLIST_H
#define TERMLIST_H

#include <fstream>
#include <string>

using namespace std;

/*!
*   \class TermList
*   \brief Read-in and print functions to be implemented by each container subclasses
*/

class TermList {
public:

  // Place the line of text into the data structure
  /*!
    *   \fn readIntoList
    *   \brief reads data from a file as terms and inserts them into selected container
    *   \param filename The file name to read from for term creation
    *   \return none
    */
  virtual void readIntoList(string filename)=0;
  //
  // Print the data iteratively
  /*!
    *   \fn printIteratively
    *   \brief prints container iteratively
    *   \param none
    *   \return none
    */
  virtual void printIteratively()=0;

  // initiates print recursive function
  /*!
    *   \fn printRecursively
    *   \brief initiates the recursive print
    *   \param none
    *   \return none
    */
  virtual void printRecursively() = 0;

  /*!
    *   \fn recursivePrint
    *   \brief print the data from a container using recursion
    *   \param none
    *   \return none
    */
  virtual void recursivePrint() {}

  // Print the data Iteratively with a pointer
  /*!
    *   \fn printPtr
    *   \brief print the data from container using an iterative pointer
    *   \param none
    *   \return none
    */
  virtual void printPtr() {}   // not pure virtual; why?

  // Evaluate the Polynomial
  /*!
    *   operator()
    *   \brief evaluates P(x) from user given x
    *   \param x the x value used to calculate P(x) from the selected container of terms
    *   \return double the P(x) value
    */
  virtual double operator()(double x) const=0;
    
};
  
#endif

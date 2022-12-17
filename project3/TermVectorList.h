/***************************************************************
Author:         Kolt Litrenta 
Filename:       TermVectorList.h  
Course:         CSC 237 Data Structures
Assignment:     Project 3
Date            November 11, 2021
Purpose:        Header file for the TermVectorList subclass
                and function implementations
***************************************************************/

/*!
*   \author Kolt Litrenta
*   \file TermVectorList.h
*   \brief Header file for the TermVectorList subclass and function implementations
*/

#ifndef TERMVECTORLIST_H
#define TERMVECTORLIST_H

#include <fstream>
#include <vector>
#include <string>
#include "TermList.h"
#include "term.h"

using namespace std;

/*!
*   \class TermVectorList
*   \brief Subclass functions used to insert into and print from object vector list
*/

// declare the subclass
class TermVectorList : public TermList {
public:

    // TermVectorList constructor
    /*!
    *   \fn Constructor
    *   \param none
    *   \return none
    */
    TermVectorList();

    // function to read file and insert terms to vector list
    /*!
    *   \fn readIntoList
    *   \brief reads data from a file as terms and inserts them into vector list
    *   \param filename The file name to read from for term creation
    *   \return none
    */
    void readIntoList(string filename);

    // function to print vector list in descending order using vector iterator
    /*!
    *   \fn printIteratively
    *   \brief prints vector list iteratively
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
    *   \brief print the data from vector list using recursion
    *   \param i The index number to print object from vector list
    *   \return none
    */
    void recursivePrint(int i);

    // operator for evaluating the polynomial
    /*!
    *   \fn operator()
    *   \brief evaluates P(x) from user given x
    *   \param x the x value used to calculate P(x) from the vector list of terms
    *   \return double the P(x) value
    */
    virtual double operator()(double x) const;

private:

    // create the vector list ThePoly of type term
    /*!
    * Vector list of type Term used to store Term objects
    */
    vector<Term> ThePoly;
};

#endif
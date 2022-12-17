/***************************************************************
Author:         Kolt Litrenta 
Filename:       TermDblLinkList.h  
Course:         CSC 237 Data Structures
Assignment:     Project 3
Date            November 11, 2021
Purpose:        Header file for the TermDblLinkList subclass
                and function implementations
***************************************************************/

/*!
*   \author Kolt Litrenta
*   \file TermDblLinkList.h
*   \brief Header file for the TermDblLinkList subclass and function implementations
*/

#ifndef TERMDBLLINKLIST_H
#define TERMDBLLINKLIST_H

#include <fstream>
#include <string>
#include "TermList.h"
#include "term.h"
#include "DblLink.h"

using namespace std;

/*!
*   \class TermDblLinkList
*   \brief Subclass functions used to insert into and print from doubly linked list
*/

// declare the subclass
class TermDblLinkList : public TermList {
public:

    // TermDblLinkList constructor
    /*!
    *   \fn Constructor
    *   \param none
    *   \return none
    */
    TermDblLinkList();

    // function to read file and insert terms to doubly linked list
    /*!
    *   \fn readIntoList
    *   \brief reads data from a file as terms and inserts them into doubly linked list
    *   \param filename The file name to read from for term creation
    *   \return none
    */
    void readIntoList(string filename);

    // function to print doubly linked list in descending order using doubly link list iterator
    /*!
    *   \fn printIteratively
    *   \brief prints doubly linked list iteratively
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
    *   \brief print the data from doubly linked list using recursion
    *   \param ListIterator The Doubly Linked List iterator used to print and increment for recursion
    *   \return none
    */
    void recursivePrint(DblLinkItr<Term> ListIt);

    // operator for evaluating the polynomial
    /*!
    *   
    *   \brief evaluates P(x) from user given x
    *   \param x the x value used to calculate P(x) from the doubly linked list of terms
    *   \return double the P(x) value
    */
    virtual double operator()(double x) const;

private:
    // create the doubly linked list ThePoly of type term
    /*!
    * Doubly linked list of type Term used to store Term objects within the doubly linked list
    */
    DblLink<Term> ThePoly;
};

#endif
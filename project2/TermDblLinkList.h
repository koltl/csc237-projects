/***************************************************************
Author:         Kolt Litrenta 
Filename:       TermDblLinkList.h  
Purpose:        Header file for the TermDblLinkList subclass
                and function implementations
***************************************************************/

#ifndef TERMDBLLINKLIST_H
#define TERMDBLLINKLIST_H

#include <fstream>
#include <string>
#include "TermList.h"
#include "term.h"
#include "DblLink.h"

using namespace std;

// declare the subclass
class TermDblLinkList : public TermList {
public:

    // TermDblLinkList constructor
    TermDblLinkList();

    // function to read file and insert terms to doubly linked list
    void readIntoList(string filename);

    // function to print doubly linked list in descending order using doubly link list iterator
    void printIteratively();

    // operator for evaluating the polynomial
    virtual double operator()(double x) const;

private:
    // create the doubly linked list ThePoly of type term
    DblLink<Term> ThePoly;
};

#endif
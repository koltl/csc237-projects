/***************************************************************
Author:         Kolt Litrenta 
Filename:       TermVectorList.h  
Purpose:        Header file for the TermVectorList subclass
                and function implementations
***************************************************************/

#ifndef TERMVECTORLIST_H
#define TERMVECTORLIST_H

#include <fstream>
#include <vector>
#include <string>
#include "TermList.h"
#include "term.h"

using namespace std;

// declare the subclass
class TermVectorList : public TermList {
public:

    // TermVectorList constructor
    TermVectorList();

    // function to read file and insert terms to vector list
    void readIntoList(string filename);

    // function to print vector list in descending order using vector iterator
    void printIteratively();

    // operator for evaluating the polynomial
    virtual double operator()(double x) const;

private:

    // create the vector list ThePoly of type term
    vector<Term> ThePoly;
};

#endif
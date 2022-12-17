/***************************************************************
Author:         Dr. Spiegel 
Filename:       Term.h   
Course:         CSC 237 Data Structures
Assignment:     Project 4
Date            December 7, 2021
Purpose:        A Term holds one term of a polynomial. A term 
		can be created, evaluated, compared, and printed
***************************************************************/

/*!
*	\author Dr. Spiegel
*	\file term.h
*	\brief A Term holds one term of a polynomial. A term can be created, evaluated, compared, and printed
*/


#ifndef TERM_H
#define TERM_H

#include <iostream>

using namespace std;

/*!
*   \class Term
*   \brief Class functions to that permit creation, retrieval, comparison, and output of Term objects
*/

class Term
{
public:
	//Constructor
	/*!
    *   \fn Constructor
    *   \param double the term's coefficient
	* 	\param int the term's exponent
    *   \return none
    */
	Term(double=0, int=0); 	//default value of 0x^0

	//Gets (No sets in immutable object)
	/*!
    *   \fn getCoefficient
    *   \brief return a term's coefficient
    *   \param none
    *   \return double
    */
	double getCoefficient() const; 		//returns the coefficient

	/*!
    *   \fn getExponent
    *   \brief return a term's exponent
    *   \param none
    *   \return int
    */
	int getExponent() const; 		//returns the exponent

	//evaluate
	/*!
    *   
    *   \brief evaluates a term with supplied x value
    *   \param x the x value used to calculate P(x)
    *   \return double the P(x) value
    */
	double operator()(double x) const; 	// evaluation of term
	
	//other
	// does exponent match the parameter? Note signature ==(Term&,int)
	/*!
    *   
    *   \brief checks if exponents match
    *   \param value the exponent to compare
    *   \return bool
    */
	bool operator==(int value); 

	// does exponent match that of the param?  Signature: ==(Term,Term)

	/*!
    *   
    *   \brief checks if exponents match
    *   \param value the exponent to compare
    *   \return bool
    */
	bool operator==(const Term &right);

    /*!
    *   
    *   \brief checks if exponents do not match
    *   \param data Term's exponent to compare
    *   \return bool true if no a match, false if a match
    */
    bool operator!=(const Term &data);

    /*!
    *   
    *   \brief adds coefficient by incoming Term coefficient
    *   \param data Term's coefficient to use for addition
    *   \return bool true if coefficient update leads to it being 0
    */
    bool operator+=(const Term &data);

    /*!
    *   
    *   \brief changes exponent to incoming exponent
    *   \param data Term's exponent to change to
    *   \return none
    */
    void operator-(const Term &data);

	// is this term's exponent less than right's? Signature <(Term&,Term&)
	/*!
    *   
    *   \brief check if term's exponent is less than right
    *   \param &right value to compare
    *   \return bool
    */
	bool operator<(Term &right) const;

    // is this term's exponent bigger than right's? Signature >(Term&,Term&)
	/*!
    *   
    *   \brief check if term's exponent is bigger than right
    *   \param &right value to compare
    *   \return bool
    */
	bool operator>(Term &right) const;


	// is this term's exponent less than right? Signature: <(Term&,int)
	/*!
    *   
    *   \brief check if term's exponent is less than right
    *   \param right value to compare
    *   \return bool
    */
	bool operator<(int right) const;

private:
	/*!
	*	coefficient value of a term
	*/
	double coefficient; //holds the coefficient value

	/*!
	*	exponent value of a term
	*/
	int exponent; //holds the exponent value

};
	// Stream insert a term
	/*
	*	stream insert a term
	*/
	ostream &operator<<(ostream &output,const Term &term); 
#endif

/***************************************************************
Author:         Dr. Spiegel 
Filename:       Term.h   
Course:         CSC 237 Data Structures
Assignment:     Project 3
Date            November 11, 2021
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

	// is this term's exponent less than right's? Signature <(Term&,Term&)
	/*!
    *   
    *   \brief check if term's exponent is less than right
    *   \param &right value to compare
    *   \return bool
    */
	bool operator<(Term &right);


	// is this term's exponent less than right? Signature: <(Term&,int)
	/*!
    *   
    *   \brief check if term's exponent is less than right
    *   \param right value to compare
    *   \return bool
    */
	bool operator<(int right);

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

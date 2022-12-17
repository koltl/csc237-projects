// File: TermArrayList.cpp
// Container of Term objects 
//   Implementations of member functions including inherited pure virtual fns.

#include <fstream>
#include <iostream>
#include <iomanip>
#include "TermArrayList.h"

using namespace std;

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
  { ifstream source(filename.c_str());

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
  { cout<<"---------------------------------"<<endl;
    cout<<"|Object  Array  Iterative       |"<<endl;
    cout<<"---------------------------------"<<endl;
    for(int i=0; i<numTerms; i++) {
//      cout<<" "<<ThePoly[i]<< "    " << ThePoly[i].getArea() << 
//	    		"    " << ThePoly[i].getPerimeter() << endl;
      cout <<  ThePoly[i] << (i < numTerms-1?" + ":"");
    }
    cout << endl << endl;
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
  { cout<<"---------------------------------"<<endl;
    cout<<"|Object  Array  Pointer         |"<<endl;
    cout<<"---------------------------------"<<endl;
    Term *now=ThePoly;
    for(int i=0; i<numTerms; i++)
      cout << "" << *(now++)  << (i < numTerms-1?" + ":"");
    cout << endl << endl;
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
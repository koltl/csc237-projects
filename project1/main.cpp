/***************************************************************
Author:         Kolt Litrenta 
Filename:       main.cpp   
Purpose:        To read in, divise, and output a polynomial
                from a user given file
***************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <list>
#include <cmath>
#include "term.h"
using namespace std;

// constant variables which holds array max sizes
const int OBJECT_ARRAY_SIZE = 9;
const int PARALLEL_ARRAY_SIZE = 9;

int parallel_array_read(fstream& inputFile, double array_of_coef[], int array_of_exponents[]);
void parallel_array_recursive(fstream& inputFile);
void parallel_array_iterative(fstream& inputFile);
void output_parallel_array_recursive(double inputCoefArray[], int inputExpntArray[], int count);
void output_parallel_array_iterative(double inputCoefArray[], int inputExpntArray[], int count);



int object_array_read(Term objArray[], fstream& inputFile);

void object_array_recursive(fstream& inputFile);
void object_array_iterative(fstream& inputFile);
void object_array_pointer_recursive(fstream& inputFile);
void output_object_array_recursive(Term objArray[], int count);
void output_object_array_pointer_recursive(Term objArray[], Term inputArray[], int count);
void output_object_array_iterative(Term objArray[], int count);

int vector_container_read(fstream& inputFile, vector<Term>& inputVector);
void vector_container_for_loop(fstream& inputFile);
void vector_container_iterative(fstream& inputFile);
void output_vector_container_for_loop(vector<Term>& inputVector);
void output_vector_container_iterative(vector<Term>& inputVector);


int main() {

    
    string filename;
    fstream inputFile;
    int userChoice;
    cout << "Provide a text file of your terms, <filename>.txt : ";
    cin >> filename;
    inputFile.open(filename);
    
    if ((!inputFile.is_open())) {
        cout << "\nError trying to open " << filename << "!  Make sure it's in the correct format\n";
        return 0;
    } else {
        do {
            cout << "\nSuccessfully opened " << filename << ".  Please choose an option below:\n";

            cout << "1. PARALLEL ITERATIVE\n";
            cout << "2. PARALLEL RECURSIVE\n";
            cout << "3. OBJECT ARRAY ITERATIVE\n";
            cout << "4. OBJECT ARRAY RECURSIVE\n";
            cout << "5. OBJECT ARRAY POINTER RECURSIVE\n";
            cout << "6. STL VECTOR FOR LOOP\n";
            cout << "7. STL VECTOR ITERATOR\n";
            cout << "8. EXIT\n";

            cout << "Choose which method to use for output (1-7, 8 to exit): ";
            cin >> userChoice;

            switch(userChoice) {
                case 1:
                    parallel_array_iterative(inputFile);
                    break;
                case 2:
                    parallel_array_recursive(inputFile);
                    break;
                case 3:
                    object_array_iterative(inputFile);
                    break;
                case 4:
                    object_array_recursive(inputFile);
                    break;
                case 5:
                    object_array_pointer_recursive(inputFile);
                    break;
                case 6:
                    vector_container_for_loop(inputFile);
                    break;
                case 7:
                    vector_container_iterative(inputFile);
                    break;
                case 8:
                    return 0;
                    break;
            }
        } while (userChoice != 8);
    }
}

void vector_container_for_loop(fstream &inputFile) {
    /*********************************************************************
	*   Function name:  vector_container_for_loop
	*   Description:  declares vector objects, initiates read in function and store count (number of elements in the vector), and invokes the appopriate output method
	*   Parameters: fstream inputFile - uses file for reading data in each line
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // declare vector of term objects
    vector<Term> objects;

    // call vector_container_read, passing the input file and objects vector, then returns element count to count variable
    int count = vector_container_read(inputFile, objects);

    // calls to function that outputs the vector using a for loop
    output_vector_container_for_loop(objects);

    // declare px, the sum of P(x)
    double px = 0;

    // declare the user input variable for x
    double userInputx;
    cout << "\nEnter a value in for x: ";
    cin >> userInputx;

    // uses a for loop to add onto px with each term
    for (vector<Term>::iterator it = objects.begin(); it != objects.end(); it++) {
        px += it->getCoefficient()*(pow(userInputx, it->getExponent()));
    }

    // outputs P(x)
    cout << "\nP(" << userInputx << ") = " << px << "\n\n";
}

void vector_container_iterative(fstream &inputFile) {
    /*********************************************************************
	*   Function name:  vector_container_iterative
	*   Description:  declares vector objects, initiates read in function and store count (number of elements in the vector), and invokes the appopriate output method
	*   Parameters: fstream inputFile - uses file for reading data in each line
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // declare vector of term objects
    vector<Term> objects;

    // call vector_container_read, passing the input file and objects vector, then returns element count to count variable
    int count = vector_container_read(inputFile, objects);
    
    // calls to function that outputs the vector using iteration
    output_vector_container_iterative(objects);

    // declare px, the sum of P(x)
    double px = 0;

    // declare the user input variable for x
    double userInputx;
    cout << "\nEnter a value in for x: ";
    cin >> userInputx;

    // uses a for loop to add onto px with each term
    for (vector<Term>::iterator it = objects.begin(); it != objects.end(); it++) {
        px += it->getCoefficient()*(pow(userInputx, it->getExponent()));
    }

    // outputs P(x)
    cout << "\nP(" << userInputx << ") = " << px << "\n\n";
}

// reads polynomial from file into the vector container
int vector_container_read(fstream& inputFile, vector<Term>& objects) {
    /*********************************************************************
	*   Function name:  vector_container_read
	*   Description:  reads from input file and constructs/inserts terms into vector container
	*   Parameters: fstream inputFile - uses file for reading data in each line, vector<Term> objects - inserts and modifies Terms in referenced vector
	*                                                                   
	*   Return Value: count - the number of inserted elements (or Terms) in the vector
	*********************************************************************/

    // set count to 0, vector starts empty
    int count = 0;

    // checks to see if file is open
    if (inputFile.is_open()) {

        // initializes coefficient, exponent values for Term object creation
        double coefficient;
        int exponent;

        // intializes match found to be false at start of read in
        bool matchFound = false;

        // loops through each line of file, inserting the left value to coefficient and right value to exponent in each line
        while (inputFile >> coefficient >> exponent) {
            
            // loops through all existing elements of vector and checks incoming exponent from file against exponents of each term, code for loop was inspired by https://stackoverflow.com/a/23383451
            for (int i = objects.size() - 1; i >= 0; i--) {
                
                // if an exponent from a given term matches incoming exponent, returns true
                if (objects.at(i).getExponent() == exponent) {

                    // declare matchFound to be true
                    matchFound = true;

                    //push back a newly created term with the matching exponent and the sum of existing coefficient with incoming coefficient
                    objects.push_back(Term(objects.at(i).getCoefficient()+coefficient, exponent));

                    //remove term with exponent that had matched with incoming exponent
                    objects.erase(objects.begin() + i );
                }
            }

            // if an exponent match wasn't found, push back new term with incoming coefficient and unique exponent.  increment element count by 1
            // if exponent match was found, do nothing and reset matchFound back to false
            if (!matchFound) {
                objects.push_back(Term(coefficient, exponent));
                count++;
            } else {
                matchFound = false;
            }
        }
    }

    // sort Terms by each unique exponent
    sort(objects.begin(), objects.end());

    // rewind file back to start
    inputFile.clear();
    inputFile.seekg(0);

    // return count to printing functions
    return count;
}

// does the actual printing for the vector container using a for loop
void output_vector_container_for_loop(vector<Term>& inputVector) {
    /*********************************************************************
	*   Function name:  output_vector_container_for_loop
	*   Description:  outputs vector container using for loop
	*   Parameters: vector<Term> objects - uses referenced vector to print out its elements
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // outputs the printing method along with delcaring P(x)
    cout << "\nVector container, printed using a for loop:\n";
    cout << "P(x) = ";

    // loops through all elements of vector, printing each term of P(x)
    for (int i = 0; i < inputVector.size(); i++) {

        // if not at start and end of vector, print '+' between terms 
        if (i != 0 && i != inputVector.size()) {
            cout << " + ";
        }

        // print out current term
        cout << inputVector[i];
    }
}

// does the actual printing for the vector container using iteration
void output_vector_container_iterative(vector<Term>& inputVector) {
    /*********************************************************************
	*   Function name:  output_vector_container_iterative
	*   Description:  outputs vector container using for loop, iteration
	*   Parameters: vector<Term> objects - uses referenced vector to print out its elements
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // outputs the printingg method along with declaring P(x)
    cout << "\nVector container, printed using iteration:\n";
    cout << "P(x) = ";

    // loops through all elements of vector using vector iterator declare at 'it'
    for (vector<Term>::iterator it = inputVector.begin(); it != inputVector.end(); it++) {

        // if not at end and start of vector, print '+' between terms
        if (it != inputVector.end() && it != inputVector.begin()) {
            cout << " + ";
        }
        //print each element using the iterator
        cout << *it;
    }
}

void object_array_recursive(fstream& inputFile) {
    /*********************************************************************
	*   Function name:  object_array_recursive
	*   Description:  declares object array, initiates read in function and store count (number of elements), and invokes the appopriate output method
	*   Parameters: fstream inputFile - uses file for reading data in each line
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // declare object array of Term
    Term objArray[OBJECT_ARRAY_SIZE];

    // call object_array_read, passing in the object array and input file, once finished store the element count
    int count = object_array_read(objArray, inputFile);

    // calls to function that outputs the object array using recursion
    output_object_array_recursive(objArray, count);
    return;
}

void object_array_pointer_recursive(fstream& inputFile) {
    /*********************************************************************
	*   Function name:  object_array_pointer_recursive
	*   Description:  declares object array, initiates read in function and store count (number of elements), and invokes the appopriate output method
	*   Parameters: fstream inputFile - uses file for reading data in each line
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // declare object array of Term
    Term objArray[OBJECT_ARRAY_SIZE];

    // call object_array_read, passing in the object array and input file, once finished store the element count
    int count = object_array_read(objArray, inputFile);
    
    // calls to function that outputs the object array using recursion
    output_object_array_pointer_recursive(objArray, objArray, count);
    return;
}

void object_array_iterative(fstream& inputFile) {
    /*********************************************************************
	*   Function name:  object_array_iterative
	*   Description:  declares object array, initiates read in function and store count (number of elements), and invokes the appopriate output method
	*   Parameters: fstream inputFile - uses file for reading data in each line
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // declare object array of Term
    Term objArray[OBJECT_ARRAY_SIZE];

    // call object_array_read, passing in the object array and input file, once finished store the element count
    int count = object_array_read(objArray, inputFile);

    // calls to function that outputs the object array using recursion
    output_object_array_iterative(objArray, count);
    return;
}

// reads polynomial from file into the object array
int object_array_read(Term objArray[], fstream& inputFile) {
    /*********************************************************************
	*   Function name:  object_array_read
	*   Description:  reads from input file and constructs/inserts terms into object array
	*   Parameters: Term objArray[] - inserts and modifies Terms in the object array, fstream inputFile - uses file for reading data in each line
	*                                                                   
	*   Return Value: count - the number of inserted elements (or Terms) in the object array
	*********************************************************************/

    // set count to 0, object array starts empty
    int count = 0;

    // checks to see if file is open
    if (inputFile.is_open()) {

        // initializes coefficient, exponent values for Term object creation
        double coefficient;
        int exponent;

        // intializes match found to be false at start of read in
        bool matchFound = false;

        // loops through each line of file, inserting the left value to coefficient and right value to exponent in each line
        while (inputFile >> coefficient >> exponent) {
            
            if (count > 0) {
                // loops through all existing elements of object array and checks incoming exponent from file against exponents of each term
                for (int x = 0; x < count; x++) {

                    //if an exponent from a given term matches incoming exponent, returns true
                    if (objArray[x].getExponent() == exponent) {
                        
                        // declare matchFound to be true
                        matchFound = true;

                        // construct temporary Term object with matching exponent and the sum of existing coefficient with incoming coefficient
                        Term temp(objArray[x].getCoefficient()+coefficient,exponent);

                        // replace object with new Term object with new coefficient 
                        objArray[x] = temp;
                    }
                }
            }

            // if an exponent match wasn't found, insert new object with incoming coefficient and unique exponent to object array.  increment element count by 1
            // if exponent match was found, do nothing and reset matchFound back to false
            if (!matchFound) {

                // if count is less than the declared object array size, follow through with insertion.  if not, print out warning and skip
                if (count <= OBJECT_ARRAY_SIZE) {
                    objArray[count] = Term(coefficient, exponent);
                    count++;
                } else {
                    cout << "\nObject array reached maximum unique terms! Skipping " << coefficient << "x^" << exponent << endl;
                }
            } else {
                matchFound = false;
            }
        }
    }

    // sorts Terms by each unique exponent
    for (int i = 0; i < count; i++) {
        for (int y = i+1; y < count; y++) {
            if (objArray[i].getExponent() < objArray[y].getExponent()) {
                Term newtemp(objArray[i].getCoefficient(), objArray[i].getExponent());
                objArray[i] = objArray[y];
                objArray[y] = newtemp;
            }
        }
    }

    // rewind file back to start
    inputFile.clear();
    inputFile.seekg(0);

    // return count to printing functions
    return count;
}

// does the actual printing for the object array using for loop
void output_object_array_iterative(Term inputArray[], int count) {
    /*********************************************************************
	*   Function name:  output_object_array_iterative
	*   Description:  outputs object array using iteration
	*   Parameters: Term inputArray[] - used to print out its elements, int count - used to check number of stored elements
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // outputs the printing method along with declaring P(x)
    cout << "\nObject array, printed iteratively:\n";
    cout << "P(x) = ";

    // loops through all elements of object array, printing each term of P(x)
    for (int i = 0; i < count; i++) {

        // if not at start, print '+' between terms
        if (i != 0) {
            cout << " + ";
        }

        // print out current term
        cout << inputArray[i];
    }

    // declare px, the sum of P(x)
    double px = 0;

    // declare the user input variable for x
    double userInputx;
    cout << "\nEnter a value in for x: ";
    cin >> userInputx;

    // uses a for loop to add onto px with each term
    for (int y = 0; y < count; y++) {
        px += inputArray[y].getCoefficient()*(pow(userInputx, inputArray[y].getExponent()));
    }

    // outputs P(x) then returns
    cout << "\nP(" << userInputx << ") = " << px << "\n\n";
}

// does the actual printing for the object array using recursion
void output_object_array_recursive(Term inputArray[], int count) {
    /*********************************************************************
	*   Function name:  output_object_array_recursive
	*   Description:  outputs object array using recursion
	*   Parameters: Term inputArray[] - used to print out its elements, int count - used to check number of stored elements
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // sets i, the number of recursive calls done.  if equal to count, return as all terms have been printed
    static int i = 0;
    if (i == count) {

        // declare px, the sum of P(x)
        double px = 0;

        // declare the user input variable for x
        double userInputx;
        cout << "\nEnter a value in for x: ";
        cin >> userInputx;

        // uses a for loop to add onto px with each term
        for (int y = 0; y < count; y++) {
            px += inputArray[y].getCoefficient()*(pow(userInputx, inputArray[y].getExponent()));
        }

        // outputs P(x) then returns
        cout << "\nP(" << userInputx << ") = " << px << "\n\n";

        // reset i back to 0
        i = i - count;
        return;
    }

    // if not at start, print '+' between terms.  if at start, output printing method along with declaring P(x)
    if (i != 0) {
        cout << " + ";
    } else {
        cout << "\nObject array, printed recursively:\n";
        cout << "P(x) = ";
    }

    // print out current term and increment i which symbolizes the amount of calls
    cout << inputArray[i];
    i++;

    output_object_array_recursive(inputArray, count);
}


// does the actual printing for the object array using pointer recursion
void output_object_array_pointer_recursive(Term inputArray[], Term objArray[], int count) {
    /*********************************************************************
	*   Function name:  output_object_array_pointer_recursive
	*   Description:  outputs object array using pointer recursion
	*   Parameters: Term inputArray[] - used to print out its elements, Term objArray[] - used for calculating P(x), int count - used to check number of stored elements
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // sets i, the number of recursive calls done.  if equal to count, return as all terms have been printed
    static int i = 0;
    if (i == count) {
        // declare px, the sum of P(x)
        double px = 0;

        // declare the user input variable for x
        double userInputx;
        cout << "\nEnter a value in for x: ";
        cin >> userInputx;

        // uses a for loop to add onto px with each term
        for (int y = 0; y < count; y++) {
            px += objArray[y].getCoefficient()*(pow(userInputx, objArray[y].getExponent()));
        }

        // outputs P(x) then returns
        cout << "\nP(" << userInputx << ") = " << px << "\n\n";

        // reset i back to 0
        i = i - count;
        return;
    }
    
    // if not at start, print '+' between terms.  if at start, output printing method along with declaring P(x)
    if (i != 0) {
        cout << " + ";
    } else {
        cout << "\nObject array, printed pointer recursively:\n";
        cout << "P(x) = ";
    }

    // print out pointer to current term and increment i which symbolizes the amount of calls
    cout << *inputArray;
    inputArray++;
    i++;
    
    output_object_array_pointer_recursive(inputArray, objArray, count);
}

void parallel_array_recursive(fstream& inputFile) {
    /*********************************************************************
	*   Function name:  parallel_array_recursive
	*   Description:  declares coefficient and exponent arrays, initiates read in function and store count (number of elements in both arrays), and invokes the appopriate output method
	*   Parameters: fstream inputFile - uses file for reading data in each line
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // declare coefficient and exponent arrays
    double array_of_coefficients[PARALLEL_ARRAY_SIZE];
    int array_of_exponents[PARALLEL_ARRAY_SIZE];

    // call parallel_array_read, passing the input file to read and the coefficient & exponent arrays to store their respective valuees.  store element count from return
    int count = parallel_array_read(inputFile, array_of_coefficients, array_of_exponents);
    
    // calls the function that outputs the coefficient and exponent arrays
    output_parallel_array_recursive(array_of_coefficients, array_of_exponents, count);
    
    // declare px, the sum of P(x)
    double px = 0;

    // declare the user input variable for x
    double userInputx;
    cout << "\nEnter a value in for x: ";
    cin >> userInputx;

    // uses a for loop to add onto px with each term
    for (int y = 0; y < count; y++) {
        px += array_of_coefficients[y]*(pow(userInputx, array_of_exponents[y]));
    }

    // outputs P(x) then returns
    cout << "\nP(" << userInputx << ") = " << px << "\n\n";
}

void parallel_array_iterative(fstream& inputFile) {
    /*********************************************************************
	*   Function name:  parallel_array_iterative
	*   Description:  declares coefficient and exponent arrays, initiates read in function and store count (number of elements in both arrays), and invokes the appopriate output method
	*   Parameters: fstream inputFile - uses file for reading data in each line
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // declare coefficient and exponent arrays
    double array_of_coefficients[PARALLEL_ARRAY_SIZE];
    int array_of_exponents[PARALLEL_ARRAY_SIZE];

    // call parallel_array_read, passing the input file to read and the coefficient & exponent arrays to store their respective valuees.  store element count from return
    int count = parallel_array_read(inputFile, array_of_coefficients, array_of_exponents);
    
    //calls the function that outputs the coefficient and exponent arrays
    output_parallel_array_iterative(array_of_coefficients, array_of_exponents, count);
    
    // declare px, the sum of P(x)
    double px = 0;

    // declare the user input variable for x
    double userInputx;
    cout << "\nEnter a value in for x: ";
    cin >> userInputx;

    // uses a for loop to add onto px with each term
    for (int y = 0; y < count; y++) {
        px += array_of_coefficients[y]*(pow(userInputx, array_of_exponents[y]));
    }

    // outputs P(x) then returns
    cout << "\nP(" << userInputx << ") = " << px << "\n\n";
}

// reads polynomial from file into a coefficient and exponent array, where a Term is related by the same index of both arrays
int parallel_array_read(fstream& inputFile, double array_of_coefficients[], int array_of_exponents[]) {
/*********************************************************************
	*   Function name:  parallel_array_read
	*   Description:  reads from input file and inserts coefficients into a coefficient array and inserts exponents, both of which are related by their indices
	*   Parameters: fstream inputFile - uses file for reading data in each line, double array_of_coefficients[] - used to insert coefficient values 
                    in this array, int array_of_exponents[] - used to insert exponent value in this array
	*                                                                   
	*   Return Value: count - the number of inserted elements in both the array_of_coefficients[] and array_of_exponents[]
	*********************************************************************/
    
    // set count to 0, both arrays start empty
    int count = 0;

    // checks to see if file is open
    if (inputFile.is_open()) {

        // initializes coefficient, exponent values for array insertion
        double coefficient;
        int exponent;

        // intializes match found to be false at start of read in
        bool matchFound = false;

        // declares newcoef which stores the sum of existing and incoming coefficients into coefficient array
        int newcoef;

        // loops through each line of file, inserting the left value to coefficient and right value to exponent in each line
        while (inputFile >> coefficient >> exponent) {
            if (count > 0) {

                // loops through all existing elements of exponent array and checks incoming exponent from file against each element
                // if match is found, set match to true and add the related coefficient to incoming coefficient
                for (int x = 0; x < count; x++) {
                    if (array_of_exponents[x] == exponent) {
                        matchFound = true;
                        newcoef = array_of_coefficients[x]+coefficient;
                        array_of_coefficients[x] = newcoef;
                    }
                }
            }

            // if an exponent match wasn't found, insert incoming coefficient and exponent to next free element of their respective arrays, increment count by 1
            //if exponent match was founnd, do nothing and reset matchfound back to false
            if (!matchFound) {

                // if count is less than the declared arry size, follow through with insertion.  if not, print out warning and skip
                if (count <= PARALLEL_ARRAY_SIZE) {
                    array_of_coefficients[count] = coefficient;
                    array_of_exponents[count] = exponent;
                    count++;
                } else {
                    cout << "\nObject array reached maximum unique terms! Skipping " << coefficient << "x^" << exponent << endl;
                }
            } else {
                matchFound = false;
            }
        }
    }

    // sorts coefficient and exponent array by exponents
    for (int i = 0; i < count; i++) {
        for (int y = i+1; y < count; y++) {
            if (array_of_exponents[i] < array_of_exponents[y]) {
                int tempCoef = array_of_coefficients[i];
                int tempExpnt = array_of_exponents[i];
                array_of_coefficients[i] = array_of_coefficients[y];
                array_of_exponents[i] = array_of_exponents[y];
                array_of_coefficients[y] = tempCoef;
                array_of_exponents[y] = tempExpnt;
            }
        }
    }

    // rewind file back to start
    inputFile.clear();
    inputFile.seekg(0);

    // return element count to printing functions
    return count;
}

// does the actual printing for the array using for loop
void output_parallel_array_iterative (double inputCoefArray[], int inputExpntArray[], int count) {
    /*********************************************************************
	*   Function name:  output_parallel_array_iterative
	*   Description:  outputs coefficient and exponent array using iteration
	*   Parameters: double inputCoefArray[] - used to output coefficient elements, int inputExpntArray[] - used to output exponent elements, int count - the number of elements in both arrays
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // outputs the printing method along with declaring P(x)
    cout << "\nParallel array, printed iteratively\n";
    cout << "P(x) = ";

    // loops through all ements of both arrays, printing the related coefficient and exponent values
    for (int i = 0; i < count; i++) {

        // if not at start, print '+' between terms
        if (i != 0) {
            cout << " + ";
        }

        // output format depending on exponent value
        if (inputExpntArray[i] > 0) {
            cout << inputCoefArray[i] << "x^" << inputExpntArray[i];
        } else if (inputExpntArray[i] == 1) {
            cout << inputCoefArray[i] << "x";
        } else {
            cout << inputCoefArray[i];
        }
    }
}

// does the actual printing for the array using recursion
void output_parallel_array_recursive (double inputCoefArray[], int inputExpntArray[], int count) {
    /*********************************************************************
	*   Function name:  output_parallel_array_recursive
	*   Description:  outputs coefficient and exponent array using recursion
	*   Parameters: double inputCoefArray[] - used to output coefficient elements, int inputExpntArray[] - used to output exponent elements, int count - the number of elements in both arrays
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // sets i, the number of recursive calls done.  if equal to count, return as all terms have been printed
    static int i = 0;
    if (i == count) {

        // reset i back to 0
        i = i - count;
        return;
    }

    // if not at start, print '+' between terms.  if at start, output printing method along with declaring P(x)
    if (i != 0) {
        cout << " + ";
    } else {
        cout << "\nParallel array, printed recursively\n";
        cout << "P(x) = ";
    }

    // output format depending on exponent value 
    if (inputExpntArray[i] > 0) {
        cout << inputCoefArray[i] << "x^" << inputExpntArray[i];
    } else {
        cout << inputCoefArray[i];
    }
    i++;
    output_parallel_array_recursive(inputCoefArray, inputExpntArray, count);
}
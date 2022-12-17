/***************************************************************
Author:         Dr. Spiegel, Kolt Litrenta 
Filename:       Treetest.cpp  
Course:         CSC 237 Data Structures
Assignment:     Project 4
Date            December 9, 2021
Purpose:        Binary Tree test driver that creates a tree
                and permits user interaction which interfaces
                to binary tree
***************************************************************/

/*!
*   \authors Kolt Litrenta, Dr. Spiegel
*   \file Treetest.cpp
*   \brief Binary search tree test driver that handles user interaction and provides an interface to the Binary Search Tree
*/

#include <iostream>
#include <string>
#include "term.h"
#include "BinarySearchTree.h"

using namespace std;

typedef BinaryTree<Term> BinTree;

/*!
*   getChoice
*   \brief return with user choice
*   \param string collection of characters available to use
*   \return char character from input
*/
char getChoice(string ok);

/*!
*   add
*   \brief interface to add Term to binary tree
*   \param BinTree Binary tree to add onto
*   \return none
*/
void add(BinTree &);

/*!
*   remove
*   \brief interface to remove Term from binary tree
*   \param BinTree Binary tree to remove Term from
*   \return none
*/
void remove(BinTree &);

/*!
*   print
*   \brief Print tree as an ordered polynomial
*   \param BinTree Binary tree to print
*   \return none
*/
void print(BinTree &);

/*!
*   treePrint
*   \brief Print tree in tree form
*   \param BinTree Binary tree to print
*   \return none
*/
void treePrint(BinTree &Tree);

/*!
*   change
*   \brief interface to change Term's exponent in place if possible
*   \param BinTree Binary tree used for node modification
*   \return none
*/
void change(BinTree &Tree);

int main()
{BinTree Tree;
 char Choice;
 do {
  cout << "Select: A)dd    R)emove     P)rint     T)ree Print    C)hange     Q)uit\n";
  Choice=getChoice("ARPTCQ");
  switch (Choice) {
   case 'A':
    // users selected add choice
    add(Tree);
    break;
   case 'P':
    // user selected print choice
    print(Tree);
    break;
   case 'R':
    // user selected remove choice
    remove(Tree);
    break;
   case 'T':
    // user selected tree print choice
    treePrint(Tree);
    break;
   case 'C':
    // user selected change choice
    change(Tree);
    break;
  }
 } while (Choice!='Q');
}

// add term to binary tree
void add(BinTree &Tree) {
  double coefficient;
  int exponent;

  // promot user for term
  cout << " Enter a Term to add >";

  // read in term
  cin >> coefficient >> exponent;

  // store insert status
  int insert = Tree.insertToTree(Term(coefficient, exponent));
  switch (insert) {
    case 0:
      cout << "\nMatch found, updating...\n";
      break;
    case 1:
      cout << "\nSuccessfully added " << Term(coefficient, exponent) << endl;
      break;
    case 2:
      cout << "\nRecord result in coefficient 0, removing...\n";
  }
}

void remove(BinTree &Tree) {
  double coefficient;
  int exponent;

  // prompt user for term
  cout << "Enter a Term to delete >";

  // read in term
  cin >> coefficient >> exponent;

  // check if Term to remove exists, if it does then delete from tree
  if (!Tree.treeSearch(Term(coefficient, exponent))) {
    cout << endl << Term(coefficient, exponent) << " Not Found\n";
  } else {
    Tree.deleteFromTree(Term(coefficient, exponent));
    cout << "\nDeleted " << Term(coefficient, exponent) << " from tree\n";
  }
}

// print binary tree in reverse order
void print(BinTree &Tree) {
  cout << "The Tree:" << endl;
  Tree.printRevOrder('+', true);
  cout << endl;
}

// print binary tree in form of a tree
void treePrint(BinTree &Tree) {
  cout << "\nThe tree, as it appears (sort of)..\n";
  Tree.treePrint(); 
}

// change Term in place if possible
void change(BinTree &Tree) {
  int oldExponent;
  int newExponent;

  // prompt user 
  cout << " Enter exponent you want to change>";

  // read in exponent to change
  cin >> oldExponent;

  if (Tree.treeSearch(Term(0, oldExponent))) {
    cout << " Enter exponent you want to change to> ";
    // read in new exponent
    cin >> newExponent;
    if (Tree.change(Term(0, oldExponent), Term(0, newExponent))) {
      cout << "\nSuccessfully changed\n";
    } else {
    cout << "\nCannot change in place, reinserting\n";
    }
  } else {
    cout << "\nCannot find exponent to change!\n";
  }
}

char getChoice(string ok)
{char ch=' ';
 do ch=toupper(cin.get()); while (ok.find(ch)==string::npos);
 cin.get(); // eat CR
 return(toupper(ch));
}

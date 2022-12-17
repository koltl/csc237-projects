/***************************************************************
Author:         Dr. Spiegel, Kolt Litrenta 
Filename:       BinrarySearchTree.cpp  
Course:         CSC 237 Data Structures
Assignment:     Project 4
Date            December 7, 2021
Purpose:        Header file for a Binary Tree
***************************************************************/

/*!
*   \authors Kolt Litrenta, Dr. Spiegel
*   \file BinarySearchTree.h
*   \brief Class and function headers for the Binary Search Tree class.
*/

#ifndef TREE_H
#define TREE_H

 template <typename eltType> class BinaryTree;

 template <typename eltType> class TreeNode {
 private:
  eltType info;
  TreeNode<eltType> *left,*right;  
  TreeNode(const eltType &data,
                        TreeNode<eltType> *lChild=NULL,TreeNode *rChild=NULL)
  {info=data;   left=lChild; right=rChild;  }
  
  friend class BinaryTree<eltType>;
 };

template <typename eltType> class BinaryTree {

public:

 // Constructor
 /*!
*   \fn Constructor
*   \param none
*   \return none
*/
 BinaryTree();

 // Place Element into Tree
 // Returns 1 if inserted, 0 if Data already in tree
 /*!
*   \fn insertToTree
*   \brief insert new element into tree
*   \param eltType The data to insert into binary tree
*   \return int Used to report the result
*/
 int insertToTree(const eltType &data);

// Change element's data
/*!
*   \fn change
*   \brief change element in tree in place if possible
*   \param eltType olddata contains a Term of exponent to locate to change from
* 	\param eltType newdata contains a Term of exponent to change to change to
*   \return int Used to report result
*/
 int change(const eltType &olddata, const eltType &newdata);

 // Search for Element in Tree
 // Assumes == is defined for eltType
 // Returns bool according to success
 /*!
*   \fn treeSearch
*   \brief search for an element in the tree and report if found
*   \param eltType data to search for in binary tree
*   \return bool Returns true is data is found, false if data is not found
*/
 bool treeSearch(const eltType &data);

 // Retrieve Element from Tree (leaving Tree Intact)
 // Precondition: Item is in Tree
 /*!
*   \fn retreiveFromTree
*   \brief retreive element from tree
*   \param eltType data to locate in binary tree
*   \return eltType Returns the element from binary tree
*/
 eltType &retrieveFromTree(const eltType &data);

 // Remove an Element from the tree
 // Pre: Element is in the Tree
 /*!
*   \fn deleteFromTree
*   \brief remove an elemen from the tree
*   \param eltType data to remove from tree if located
*   \return none
*/
 void deleteFromTree(const eltType &data);

 // Display Tree using InOrder Traversal
 /*!
*   \fn inorder
*   \brief print the tree in order
*   \return none
*/
 void inorder() const;

 // Display Tree using PreOrder Traversal
  /*!
*   \fn preorder
*   \brief print the tree in preorder
*   \return none
*/
 void preorder() const;

 // Display Tree using PostOrder Traversal
/*!
*   \fn postorder
*   \brief print the tree in post order
*   \return none
*/
 void postorder() const;
 
 // Breadth first print
/*!
*   \fn treePrint
*   \brief print the tree
*   \return none
*/
 void treePrint() const;

/*!
*   \fn revorder
*   \brief print tree in reverse order
*   \return none
*/
 void revorder() const;

/*!
*   \fn printRevOrder
*   \brief facilatate the print in reverse order
*   \param symbol symbol to print between data
*   \param first if true, do not print symbol
*   \return none
*/
 void printRevOrder(char symbol, bool first) const;
 
private:

 TreeNode<eltType> *root;

 // Display Tree using InOrder Traversal
 /*!
    *   \fn printInorder
    *   \brief recursively print tree in order
    *   \param TreeNode Node to print from, assumed root
    *   \return none
    */
 void printInorder(TreeNode<eltType> *) const;

 // Display Tree using PreOrder Traversal
 /*!
    *   \fn printPreorder
    *   \brief recursively print tree in preorder
    *   \param TreeNode Node to print from, assumed root
    *   \return none
    */
 void printPreorder(TreeNode<eltType> *) const;

 // Display Tree using PostOrder Traversal
 /*!
    *   \fn printPostorder
    *   \brief recursively print tree in postorder
    *   \param TreeNode Node to print from, assumed root
    *   \return none
    */
 void printPostorder(TreeNode<eltType> *) const;

 // Display Tree using reverse order traversal
 /*!
    *   \fn printReverse
    *   \brief recursively print tree in reverse order
    *   \param TreeNode Node to print from, assumed root
    *   \return none
    */
 void printReverse(TreeNode<eltType> *) const;
 
 /*!
    *   \fn treePrintHelper
    *   \brief provides interface to facilitate tree printing
    *   \param TreeNode Node to pass to actual print function
    *   \return none
    */
 void treePrintHelper(TreeNode<eltType> *) const;

};

#endif

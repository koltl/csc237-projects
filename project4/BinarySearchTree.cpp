/***************************************************************
Author:         Dr. Spiegel, Kolt Litrenta 
Filename:       BinrarySearchTree.cpp  
Course:         CSC 237 Data Structures
Assignment:     Project 4
Date            December 7, 2021
Purpose:        Function implementations for the Binary Search Tree.
                Implements key functions usch as insertion, removal
                and modification of nodes of a given data type
***************************************************************/

/*!
*   \authors Kolt Litrenta, Dr. Spiegel
*   \file BinarySearchTree.cpp
*   \brief Function implementations for the Binary Search Tree class.
*/

#include <iostream>
#include <string>
#include <queue>
#include "BinarySearchTree.h"

using namespace std;

// Constructor
template <typename eltType> BinaryTree<eltType>::BinaryTree()
{root=NULL;}

// Place Element into Tree
// Returns 1 if inserted, 0 if data already in tree
template <typename eltType>
	  int BinaryTree<eltType>::insertToTree(const eltType &data)
{if (root==NULL) { // Empty Tree
  root=new TreeNode<eltType>(data);
  return(1);
 }
 // Search for spot to put data; We only stop when we get to the bottom (NULL)
 TreeNode<eltType> *t=root,*parent;
 while(t!=NULL) {
   if (t->info==data) { // data already in Tree
     // add coefficients
     //t->info+=data;  // updated code
     
     if (t->info+=data) {
       return(0);
     } else {
       deleteFromTree(t->info);
       return(2);
     }
     //return(0); 
   }
   parent=t; // Set the trail pointer to the ancestor of where we're going
   if (data<t->info) 
     t=t->left;
   else 
     t=t->right;
 }
 // Found the spot; insert node.
 if (data<parent->info) parent->left=new TreeNode<eltType>(data);
 else parent->right=new TreeNode<eltType>(data);
 return(1);
}

template <typename eltType> int BinaryTree<eltType>::change(const eltType &olddata, const eltType &newdata) {
  eltType datanew = newdata;
  TreeNode<eltType> *t = root;
  TreeNode<eltType> *ttrail = t;
  TreeNode<eltType> *ttrailtrail = ttrail;
  //TreeNode<eltType> *newnode;
  TreeNode<eltType> *oldnode;

  // find data with exponent to change from
  while (t && t->info != olddata) {
    if (olddata < t->info) {
      ttrailtrail = ttrail;
      ttrail = t;
      t = t->left;
    } else {
      ttrail = t;
      t = t->right;
    }
  }

  // check if exponent to change from is not found
  if (t->info != olddata) {
    cout << "\ncould not find base exponent\n";
    return 0;
  }

  if (t->left && t->right) {
    // has two children
    if (newdata > t->left->info && newdata < t->right->info) {
      // Change in place can occur
      t->info-newdata;
      return 1;
    } else {
      // change in place cannot occur, reinsert
      datanew+=t->info;
      deleteFromTree(t->info);
      insertToTree(datanew);
      return 0;
    }
  } else if (!t->left && !t->right) {
    // has no children

    if (ttrail->left == t) {
      // extreme value
      if (newdata < ttrail->info) {
        // change in place can occur
        t->info-newdata;
        return 1;
      } else {
        // change in place cannot occur, reinster
        datanew+=t->info;
        deleteFromTree(t->info);
        insertToTree(datanew);
        return 0;
      }
    } else if (ttrail->right == t) {
      if (newdata > ttrail->info && newdata < ttrailtrail->info) {
        // change can occur
        t->info-newdata;
        return 1;
      } else {
        // change in place cannot occur, reinsert
        datanew+=t->info;
        deleteFromTree(t->info);
        insertToTree(datanew);
        return 0;
      }
    } else if (t == root) {
      // value to change is in root
      t->info-newdata;
      return 1;
    }

    
  } else if ((t->left && !t->right) || (!t->left && t->right)) {
    // has one child

    if (t->left && (ttrail->left == t)) {
    // left child that has a left child

      if (newdata > t->left->info && newdata < ttrail->info) {
        // change in place can occur
        t->info-newdata;
        return 1;
      } else {
        // change in place cannot occur, reinsert
        datanew+=t->info;
        deleteFromTree(t->info);
        insertToTree(datanew);
        return 0;
      }
    } else if (t->right && (ttrail->left == t)) {
      // left child that has a right child
      if (newdata < t->right->info && newdata < ttrail->info) {
        // change in place can occur
        t->info-newdata;
        return 1;
      } else {
        // change in place cannot occur, reinsert
        datanew+=t->info;
        deleteFromTree(t->info);
        insertToTree(datanew);
        return 0;
      }
    } else if (t->left && (ttrail->right == t)) {
      // right child that has a left child

      if (newdata > t->left->info && newdata > ttrail->info) {
        // change in place can occur
        t->info-newdata;
        return 1;
      } else {
        // change in place cannot occur, reinsert
        datanew+=t->info;
        deleteFromTree(t->info);
        insertToTree(datanew);
        return 0;
      }
    } else if (t->right && (ttrail->right == t)) {
      // right child that has a right child
      if (newdata > t->right->info && newdata > ttrail->info) {
        // change in place can occur
        t->info-newdata;
        return 1;
      } else {
        // change in place cannot occur, reinsert
        datanew+=t->info;
        deleteFromTree(t->info);
        insertToTree(datanew);
        return 0;
      }
    }
    
  }
  return 1;
}

template <typename eltType> void BinaryTree<eltType>::printRevOrder(char symbol, bool first) const {
  if (first) {
    printReverse(root);
  } else {
    cout << " " << symbol << " ";
  }
  
}

// Search for Element in Tree
// Assumes == is defined for eltType
// Returns Ptr to Elt if Found, NULL otherwise
template <typename eltType>
	bool BinaryTree<eltType>::treeSearch(const eltType &key)
{TreeNode<eltType> *t=root;
 while (t && t->info != key)
   if (key < t->info) 
     t=t->left;
   else 
     t=t->right;
 return(t);	// auto convert int to bool
}

// Retrieve Element from Tree (leaving Tree Intact)
// Precondition: Item is in Tree
template <typename eltType>
   eltType &BinaryTree<eltType>::retrieveFromTree(const eltType &key) 
{TreeNode<eltType> *t;
 for (t=root;t->info!=key;)
  if (key<t->info) t=t->left;
  else t=t->right;
 return(t->info);
}

// Remove an Element from the tree
// Precondition: Element is in the Tree; 
template <typename eltType>
      void BinaryTree<eltType>::deleteFromTree(const eltType &data)
{TreeNode<eltType> *nodeWithData,*nodeToDelete,*t=root,*trailT=NULL;
 // Find spot
 while (t->info!=data) {  // safe because of precondition
  trailT=t;
  if (data<t->info) t=t->left;
  else t=t->right;
 }
 nodeWithData=t;  // Hold onto the data Node for later deletion
 // Case 1: Leaf?
 if (!(nodeWithData->left) && !(nodeWithData->right)) {
  // No Subtrees, node is leaf...Wipe it
  // Is it the root?
  if (nodeWithData==root)
    root=NULL;
  else if (trailT->right==nodeWithData) // Parent's right child
    trailT->right=NULL;
  else 
    trailT->left=NULL;
  nodeToDelete=nodeWithData;    // free this at the end
 }
 else if (!(nodeWithData->left)) {  
  // If 1st condition false and this one's true, there's a right subtree
  if (!trailT) { // Node to delete is root and there is no left subtree
    nodeToDelete=root;
    root=root->right;
  }
  else { // Point parent's pointer to this node to this node's right child
    if (trailT->right==nodeWithData) 
      trailT->right=nodeWithData->right;
    else 
      trailT->left=nodeWithData->right;
    nodeToDelete=nodeWithData;
  }
 }
 else if (!(nodeWithData->right)) {  
   // If 1st 2 conditions false and this one's true, there's a left subtree
   if (!trailT) { // Node to delete is root and there is no left subtree
     nodeToDelete=root;
     root=root->left;
   }
   else {// Otherwise, move up the right subtree
     if (trailT->right==nodeWithData) 
        trailT->right=nodeWithData->left;
     else 
        trailT->left=nodeWithData->left;
     nodeToDelete=nodeWithData;
   }
 } 
 else { // If you make it here, node has two children
   // Go to rightmost node in left subtree; we know there's a right child...
  for (trailT=nodeWithData,t=nodeWithData->left;
                                        t->right!=NULL;trailT=t,t=t->right);
  // Want to copy data from node with 0 or 1 child to node with data to delete 
  // Place node data in NodeWithData
  nodeWithData->info=t->info;
   // Set the parent of source node to point at source node's left child 
   //   (We know it hasn't a right child. Also ok if no left child.)
  if (trailT==nodeWithData) 
    // Need to point parent correctly. 
    //   See if after the we went left there was no right child
    //   If there was no right child, this is rightmost node in left subtree
    trailT->left=t->left;
  else // we did go right; after going left, there was a right child
   // rightmost node has no r. child, so point its parent at its l. child 
   trailT->right=t->left;
  nodeToDelete=t;
 }
 delete nodeToDelete;
}

// Need Helper to Recursively Print the Tree
template <typename eltType>
     void BinaryTree<eltType>::printInorder(TreeNode<eltType> *t) const
//void printTheTree(TreeNode *T)
{if (t) {
  printInorder(t->left);
  cout << t->info << endl;
  printInorder(t->right);
 }
}

// print tree in reverse order, needed to print polynomial
template <typename eltType>
     void BinaryTree<eltType>::printReverse(TreeNode<eltType> *t) const
//void printTheTree(TreeNode *T)
{
  if (t) {
    printReverse(t->right);
    if (t->right) {
      // if child exists, print +
      printRevOrder('+', false);
    }
    cout << t->info;
    if (t->left) {
      // if child exists, print +
      printRevOrder('+', false);
    }
    printReverse(t->left);
 }
}

// Display Tree using InOrder Traversal
template <typename eltType> void BinaryTree<eltType>::inorder() const
{printInorder(root);}

// Need Helper to Recursively Print the Tree
template <typename eltType>
   void BinaryTree<eltType>::printPreorder(TreeNode<eltType> *t) const
//void printTheTree(TreeNode *t)
{if (t) {
  cout << t->info << endl;
  printPreorder(t->left);
  printPreorder(t->right);
 }
}

// Display Tree using InOrder Traversal
template <typename eltType> void BinaryTree<eltType>::preorder() const
{printInorder(root);}

// Need Helper to Recursively Print the Tree
template <typename eltType>
  void BinaryTree<eltType>::printPostorder(TreeNode<eltType> *t) const
//void printTheTree(TreeNode *t)
{if (t) {
  printPostorder(t->left);
  printPostorder(t->right);
  cout << t->info << endl;
 }
}

// Display Tree using InOrder Traversal
template <typename eltType> void BinaryTree<eltType>::postorder() const
{printInorder(root);}

template <typename eltType> void BinaryTree<eltType>::treePrint() const
{treePrintHelper(root);}

template <typename eltType> void BinaryTree<eltType>::
                        treePrintHelper(TreeNode<eltType> *root) const
{queue<TreeNode<eltType> *> Q;
 // A dummy node to mark end of level
 TreeNode<eltType> *dummy=new  TreeNode<eltType>(-1);
 if (root) {
   cout << root->info << " " << endl;
   Q.push(root->left);
   Q.push(root->right);
   Q.push(dummy);
 }
 TreeNode<eltType> *t=root;
 while (!Q.empty()) {
  t=Q.front();
  Q.pop();
  if (t==dummy) {
   if (!Q.empty()) 
    Q.push(dummy);
   cout << endl;
  }
  else if (t) {
   cout << t->info << " ";
   Q.push(t->left);
   Q.push(t->right);
  } 
 }
}

#include "term.h"
template class BinaryTree<Term>;

/***************************************************************
Author:         Dr. Spiegel 
Filename:       Node.h 
Course:         CSC 237 Data Structures
Assignment:     Project 3
Date            November 11, 2021 
Purpose:        Node definition for the doubly linked list
***************************************************************/

/*!
* \author Dr. Spiegel
* \file Node.h
* \brief Header file for the Node class and its implementation
*/

#ifndef NODE_H
#define NODE_H

//using namespace std;

// Need to prototype template classes if they are to be friends
template <class eltType> class DblLink;
template <class eltType> class DblLinkItr;

/*!
*	\class Node
*	\brief Definition for a node and its pointers
*/

template <class eltType> class Node
{	private:
		Node(eltType info, Node *pLink = 0, Node *rLink=0) 
				   : data(info), prev(pLink), next(rLink) {};
		eltType data;
		Node*	prev; 
		Node*	next;
	friend class DblLink<eltType>;
	friend class DblLinkItr<eltType>;
};

#endif


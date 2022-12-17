/***************************************************************
Author:         Kolt Litrenta 
Filename:       DblLink.h  
Purpose:        Provide Doubly Linked List container and
                iterator functionality
***************************************************************/

#ifndef _DblLink_
#define _DblLink_
#include <iostream>
using namespace std;

template <typename eltType> class DblLink;
template <typename eltType> class DblLinkItr;


// Node class for definining nodes in doubly linked list
template <typename eltType> class Node
{	private:
        // Node constructor, storage data and link its previous and forward neighbors
		Node(eltType info, Node *pLink = 0, Node *rLink=0) 
				   : data(info), prev(pLink), next(rLink) {};
		eltType data;
		Node*	prev; // points to previous node if applicable
		Node*	next; // points to forward (next) node if applicable
        
    // is friend of DblLink and DblLinkItr classes for access
	friend class DblLink<eltType>;
	friend class DblLinkItr<eltType>;
};

//Doubly linked list class
template <typename eltType> class DblLink {

public:
    DblLink(); // Constructs empty Doubly Linked list
    DblLink(DblLink&); // Constructor for deep copy of existing doubly linked list
    ~DblLink(); // Destructor for a doomed doubly linked list

    // assignment operator to assign a doubly linked link to an existing one; initiates deep copy
    DblLink& operator=(const DblLink&);
    
    // insert element of eltType into doubly linked list in ordered fashion
    void insert(eltType);

    // remove element of eltType from doubly linked list in ordered fashion
    void remove(eltType);


private:
    // points to the first element of doubly linked list
    Node<eltType>* head;

    // points to the last elemeent of doubly linked list
    Node<eltType>* tail;

    // copy head and tail functions necessary for deep copy
    Node<eltType>* copy(Node<eltType>*);
    Node<eltType>* copyT(Node<eltType>*);

    // release doubly linked list nodes
    void destroy(Node<eltType>*);


// declared iterator as friend for access
friend class DblLinkItr<eltType>;

};

// iterator for doubly linked list class
template <typename eltType> class DblLinkItr {
public:

    // constructor for doubly linked list iterator
    DblLinkItr(const DblLink<eltType> &list);

    // point iterator to start (head) of doubly linked list
    void start();
    void end();

    // check if doubly linked list is emtpy
    bool isEmpty();

    // check if node is the last (tail) node of doubly linked list
    bool isLastNode();

    // check if node is the first (head) node of doubly linked list
    bool isFirstNode();

    // ++ operator to increment to the next (right) node
    DblLinkItr& operator++() {
        current = current->next;
        return *this;
    }

    DblLinkItr operator++(int) {
        DblLinkItr tmp = *this;
        ++(*this);
        return tmp;
    }
    
    // -- operator to decrement to the previous (left) node
    DblLinkItr& operator--() {
        current = current->prev;
        return *this;
    }

    // return data of current node
    eltType operator( )() {
        return current->data;
    }


private:
    const DblLink<eltType> &ListRef;

    // current points to node currently pointed to
    Node<eltType> *current;
};

// construct empty doubly linked list with head set at null
template <typename eltType> DblLink<eltType>::DblLink() : head(NULL)
{}

// doubly linked list destructor, frees all nodes of doubly linked list
template <typename eltType> DblLink<eltType>::~DblLink() {
    /*********************************************************************
	*   Function name:  start
	*   Description:  sets doubly linked list iterator at the head (start) of doubly linked list
	*   Parameters: none
	*                                                                   
	*   Return Value: none
	*********************************************************************/
    destroy(head);
}

// doubly linked list copy constructor, initiates deep copy functions starting from both head and tail
template <typename eltType> DblLink<eltType>::DblLink(DblLink<eltType> &cl) {
    /*********************************************************************
	*   Function name:  DblLink
	*   Description:  constructs new doubly linked list based off of existing doubly linked list
	*   Parameters: DblLink<eltType> cl - list to construct from
	*                                                                   
	*   Return Value: none
	*********************************************************************/
    head = copy(cl.head);
    tail = copyT(cl.tail);
}

template <typename eltType> DblLink<eltType> &DblLink<eltType>::operator = (const DblLink<eltType>& list) {
    /*********************************************************************
	*   Function name:  assignment operator (=)
	*   Description:  initiates deep copy of existing doubly linked list to new doubly linked list
	*   Parameters: const DblLink<eltType> list - list to copy from
	*                                                                   
	*   Return Value: none
	*********************************************************************/
    if (this != &list) {
        destroy(head);
        head = copy(list.head);
        tail = copyT(list.tail);
    }

    return *this;
}

// deep copy from head to tail
template <typename eltType> Node<eltType>* DblLink<eltType>::copy(Node<eltType>* listPtr){
    /*********************************************************************
	*   Function name:  copy
	*   Description:  performs deep copy of doubly linked list starting from head of existing doubly linked list
	*   Parameters: Node<eltType> listPtr, used to point to a node to copy its data
	*                                                                   
	*   Return Value: first - the first node of the list
	*********************************************************************/
    if (listPtr != NULL) {
        Node<eltType>* first = NULL;
        Node<eltType>* last = NULL;
        first = last = new Node<eltType>(listPtr->data, NULL);
        Node<eltType>* source = listPtr->next;

        // while source is not NULL, keep progressing through nodes for copy
        while (source != NULL) {
            //last->prev->next = last->next;
            last->next = new Node<eltType>(source->data, NULL);
            source = source->next;
            last=last->next;
        }

        return (first);

    }
    return NULL;
}

// deep copy from tail to head
template <typename eltType> Node<eltType>* DblLink<eltType>::copyT(Node<eltType>* listPtr) {
    /*********************************************************************
	*   Function name:  copyT
	*   Description:  performs deep copy of doubly linked list starting from tail of existing doubly linked list
	*   Parameters: Node<eltType> listPtr, used to point to a node to copy its data
	*                                                                   
	*   Return Value: first - the last node of the list
	*********************************************************************/
    if (listPtr != NULL) {
        Node<eltType>* first = NULL;
        Node<eltType>* last = NULL;
        first = last = new Node<eltType>(listPtr->data, NULL);
        Node<eltType>* source = listPtr->prev;

        // while source is not NULL, keep progressing through nodes for copy
        while (source != NULL) {
            //last->prev->next = last->next;
            last->prev = new Node<eltType>(source->data, NULL);
            source = source->prev;
            last=last->prev;
        }
        return (first);
    }
    return NULL;
}

// place element of eltType in doubly linked list in ordered fashion
template <typename eltType> void DblLink<eltType>::insert(eltType x) {
    /*********************************************************************
	*   Function name:  insert
	*   Description:  inserts element of eltType into doubly linked list in ordered fashion
	*   Parameters: eltType x - the element to insert into doubly linked list in order
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    
    // if head == null (empty list), inserted node will become head/tail
    if (head == NULL) {
        head = new Node<eltType>(x, NULL, NULL);
        tail = head;
    } else {
        // declare tracking nodes
        Node<eltType>* p = head->next;
        Node<eltType>* trailp = head;
        Node<eltType>* trailtrailp = head->prev;

        while (p != NULL && !(x < trailp->data)) {
            trailtrailp = trailp;
            trailp = p;
            p = p->next;
        }

        // if incoming element already exists, inform user and skip insertion, avoiding duplicate value
        if (x == trailp->data) {
            cout << x << " is already an element of the list!  Skipping...\n";
            return;
        }

        if (x < head->data) {
            // if incoming element is less than head, make new head node
            head = new Node<eltType>(x, NULL, trailp);
            trailp->prev = head;
        } else if (x < trailp->data) {
            // if incoming element is larger than trailp, create new node between trailtrailp and trailp
            trailp->prev = new Node<eltType>(x, trailtrailp,trailp);
            trailtrailp->next = trailp->prev;
        } else if (p == NULL) {
            // if incoming element is larger than tail, make it tail
            trailp->next = new Node<eltType>(x, trailp, NULL);
            tail = trailp->next;
        }
    }
}

// remove element of eltType from doubly linked list
template <typename eltType> void DblLink<eltType>::remove(eltType x) {
    /*********************************************************************
	*   Function name:  remove
	*   Description:  removes element of eltType from ordered doubly linked list
	*   Parameters: eltType x - the element to remove from doubly linked list in order
	*                                                                   
	*   Return Value: none
	*********************************************************************/

    // check if head is null, this indicates that the doubly linked list is empty
    if (head == NULL) {
        cout << "List is currently empty... no element to remove!\n";
    } else {
        
        // declare tracking nodes
        Node<eltType>* p = head;
        Node<eltType>* trailp = NULL;

        // progress if tracking node is not null or equal to element for removal
        while (p != NULL && !(p->data == x)) {
            trailp = p;
            p = p->next;
        }

        if (head->data == x && tail->data == x) {
            head = NULL;
            tail = NULL;
            delete p;
            return;
        }

        if (p != NULL) {
            if (p == head) {
                // if p is head, point head to next node and makes its previous pointer NULL
                Node<eltType>* temp = head->next;
                head = head->next;
                temp->prev = NULL;
            } else if (p == tail) {
                // if p is tail, point tail to previous node and make its next pointer NULL
                Node<eltType>* temp = tail->prev;
                tail = tail->prev;
                temp->next = NULL;
            } else {
                // if p neither head or tail, just remove it between its neighboring nodes
                Node<eltType>* temp = p->next;
                trailp->next = p->next;
                p->next->prev = trailp;
            }
        } else {
            cout << x << " is not an element of the list!  Skipping...\n";
        }

        // delete the node p
        delete p;
        
    }
}

// delete all nodes in doubly linked list, starting from head
template <class eltType> void DblLink<eltType>::destroy(Node<eltType> *listPtr) {
    /*********************************************************************
	*   Function name:  destroy
	*   Description:  destroys an existing doubly linked list by removing all of its nodes starting from head
	*   Parameters: Node<eltType> listPtr - pointer to start node to progressively delete from
	*                                                                   
	*   Return Value: none
	*********************************************************************/
    while (listPtr != NULL) {
        Node<eltType> *toDelete = listPtr;
        listPtr = listPtr->next;
        delete toDelete;
    }
}

/////////////////////////////////////////////////////////////////////////
/////////////  Doubly Linked List iterator functions /////////////
/////////////////////////////////////////////////////////////////////////

// constructor for doubly linked list iterator
template <typename eltType> 
DblLinkItr<eltType>::DblLinkItr(const DblLink<eltType> &list): 
  						 ListRef(list),current(NULL) 
    /*********************************************************************
	*   Function name:  DblLinkItr
	*   Description:  constructs doubly link list iterator for list
	*   Parameters: list - doubly linked list to create iterator for
	*                                                                   
	*   Return Value: none
	*********************************************************************/
{}

// sets the iterator to the head of the doubly linked list
template <typename eltType> void DblLinkItr<eltType>::start(void) {
    /*********************************************************************
	*   Function name:  start
	*   Description:  sets doubly linked list iterator at the head (start) of doubly linked list
	*   Parameters: none
	*                                                                   
	*   Return Value: none
	*********************************************************************/
    current = ListRef.head;
}

// sets the iterator to the end of the doubly linked list
template <typename eltType> void DblLinkItr<eltType>::end(void) {
    /*********************************************************************
	*   Function name:  end
	*   Description:  sets doubly linked list iterator at the tail (end) of doubly linked list
	*   Parameters: none
	*                                                                   
	*   Return Value: none
	*********************************************************************/
    current = ListRef.head;
    while (current->next != NULL) {
        current = current->next;
    }

    //current = ListRef.tail;
}

// returns if doubly linked list is empty by checking if head is null
template <typename eltType> bool DblLinkItr<eltType>::isEmpty(void) {
    /*********************************************************************
	*   Function name:  isEmpty
	*   Description:  checks if doubly linked list is empty
	*   Parameters: none
	*                                                                   
	*   Return Value: boolean value true if head is NULL
	*********************************************************************/
    return ListRef.head == NULL;
}

// returns if current node is the last (tail) node of doubly linked list
template <typename eltType> bool DblLinkItr<eltType>::isLastNode(void) {
    /*********************************************************************
	*   Function name:  isLastNode
	*   Description:  checks if current node is the last (tail) node of doubly linked list
	*   Parameters: none
	*                                                                   
	*   Return Value: bool vlaue true if current node is the tail of doubly linked list
	*********************************************************************/
    return ListRef.tail == current;
}

// returns if the current node is the first (head) node of doubly linked list
template <typename eltType> bool DblLinkItr<eltType>::isFirstNode(void) {
    /*********************************************************************
	*   Function name:  isFirstNode
	*   Description:  checks if current node is the first (head) node of doubly linked list
	*   Parameters: none
	*                                                                   
	*   Return Value: bool vlaue true if current node is the head of doubly linked list
	*********************************************************************/
    return ListRef.head == current;
}


#endif
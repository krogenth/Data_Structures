//*************************************************************************************************
//										SPECIFICATION FILE
/*
Date:
Author:
Project: Reverse-Linked Circular Recursive List
Filename: OrdList.h
Purpose: This file contains the specification for an ascending Ordered List Class. The list is implemented
with a reverse-linked structure, and uses recursion to access and modify elements in the list.
Insert, Delete, Clear, Retrieve, Print, and PrintReverse, are wrapper methods for their
recursive counterparts. The class containts 8 public methods, 3 overloaded operators, 7 protected methods,
copy constructor and destructor.

Assumptions: 1) KeyType is defined as the a programmer defined data type and is used to order the list.
2) Relational operators are defined on the primitive datatype that is typedefined as KeyType
3) ItemType is defined to contain a field named key which is defined of type KeyType
4) The list cannot hold elements with duplicate keys.
5) The list is sorted in ascending order.

Exceptions Thrown:
OutOfMemoryException		//thrown when client tries to insert and there is no memory remaining.
RetrieveOnNULLException		//thrown when currPos is nullptr on attempt to retrieve
RetrieveOnEmptyException	//thrown when there are no elemenets on attempt to retrieve

//*************************************************************************************************
//										Summary of Methods
public:

BinaryTree();											//to create a BinaryTree object
~BinaryTree();											//to kill a BinaryTre object
BinaryTree(const BinaryTree& orig);						//to copy a BinaryTree object
void FirstPosition() const;								//to set currPos to the first position in the BinaryTree object by in-order(nullptr if empty)
void NextPosition() const;								//to set currPos to the next position in the BinaryTree object by in-order(nullptr if empty or at end of the BinaryTree object)
void PrevPosition() const;								//to set currPos to the previous position in the BinaryTree object by in-order(nullptr if empty or at beginning of the BinaryTree object)
void LastPosition() const;								//to set currPos to the last position in the BinaryTree object by in-order(nullptr if empty)
bool IsEmpty() const;									//to check if the BinaryTree object is empty
bool IsFull();											//to check if the BinaryTree object is full
bool EndofList() const;									//to check if the BinaryTree object's currPos is at the end of the BinaryTree object by in-order
bool StartOfList() const;								//to check if the BinaryTree object's currPos is at the start of the BinaryTree object by in-order
ItemType Retrieve();									//to return what currPos currently points to(Find() should be called first, please)
bool Find(KeyType target);								//to find a key within the BinaryTree object
void Insert(ItemType newItem);							//to insert an element into the BinaryTree object
void Delete();											//to delete what currPos currently points to
void Clear();											//to remove all elements within the BinaryTree object
int ReturnLength() const;								//to return the number of elements within the BinaryTree object
bool IsBalanced();										//to return if the BinaryTree object is "balanced"(Due to how this implementation works, the BinaryTree object is always balanced).
void operator= (const BinaryTree& orig);				//to copy an existing BinaryTree object's data to another BinaryTree object
BinaryTree operator+ (const BinaryTree& rtOp) const;	//to OR 2 BinaryTree object's data into 1 BinaryTree object
BinaryTree operator- (const BinaryTree& rtOp) const;	//to !AND 2 BinaryTree object's data into 1 BinaryTree object
bool operator== (const BinaryTree& rtOp) const;			//to compare 2 BinaryTre objects to each other
bool operator!= (const BinaryTree& rtOp) const;			//to compare 2 BinaryTre objects to each other
void PrintScreen(void(*func)(BinaryTree));				//to print the contents of the BinaryTree objects data
void PrintFile(void(*func)(BinaryTree));				//to print the contents of the BinaryTree objects data
void PrintReverse(void(*func)(BinaryTree));				//to print the contents of the BinaryTree objects data
void PrintAsExists(void(*func)(BinaryTree));			//to print the contents of the BinaryTree objects data

protected:

	node<T> * Allocate();								//to allocate more Heap space for use
	void MakeTree(node<T> *arr, size_t arrCount);		//to create a "complete" BinaryTree object(this is abused by Insert, Delete, operator+, and operator-)
*/
//*************************************************************************************************

#pragma once
#include "Node.h"

template <class T>
class BinaryTree
{
public:
	//PUBLIC METHODS: 
	BinaryTree();
	/*
	Purpose: to create a BinaryTree object
	Pre: nothing
	Post: a BinaryTree object is born
	*/

	~BinaryTree();
	/*
	Purpose: to kill a BinaryTre object
	Pre: a BinaryTree object exists
	Post: the BinaryTree object no longer exists
	*/

	BinaryTree(const BinaryTree& orig);
	/*
	Purpose: to copy a BinaryTree object
	Pre: a BinaryTree object exists
	Post: a copy of the existing BinaryTree object is born
	*/

	void FirstPosition() const;
	/*
	Purpose: to set currPos to the first position in the BinaryTree object by in-order(nullptr if empty)
	Pre: a BinaryTree exists
	Post: the BinaryTree object's currPos is set the the first position by in-order(nullptr if empty)
	*/

	void NextPosition() const;
	/*
	Purpose: to set currPos to the next position in the BinaryTree object by in-order(nullptr if empty or at end of the BinaryTree object)
	Pre: a BinaryTree exists
	Post: the BinaryTree object's currPos is set the the next position by in-order(nullptr if empty or at end of the BinaryTree object)
	*/

	void PrevPosition() const;
	/*
	Purpose: to set currPos to the previous position in the BinaryTree object by in-order(nullptr if empty or at beginning of the BinaryTree object)
	Pre: a BinaryTree exists
	Post: the BinaryTree object's currPos is set the the next position by in-order(nullptr if empty or at beginning of the BinaryTree object)
	*/

	void LastPosition() const;
	/*
	Purpose: to set currPos to the last position in the BinaryTree object by in-order(nullptr if empty)
	Pre: a BinaryTree exists
	Post: the BinaryTree object's currPos is set the the last position by in-order(nullptr if empty)
	*/

	bool IsEmpty() const;
	/*
	Purpose: to check if the BinaryTree object is empty
	Pre: a BinaryTree exists
	Post: true if the BinaryTree object is empty, false otherwise
	*/

	bool IsFull();
	/*
	Purpose: to check if the BinaryTree object is full
	Pre: a BinaryTree exists
	Post: true if the BinaryTree object is full, false otherwise
	*/

	bool EndofList() const;
	/*
	Purpose: to check if the BinaryTree object's currPos is at the end of the BinaryTree object by in-order
	Pre: a BinaryTree exists
	Post: true if currPos is at the last element in the BinaryTree object, false otherwise
	*/

	bool StartOfList() const;
	/*
	Purpose: to check if the BinaryTree object's currPos is at the start of the BinaryTree object by in-order
	Pre: a BinaryTree exists
	Post: true if currPos is at the first element in the BinaryTree object, false otherwise
	*/

	ItemType Retrieve();
	/*
	Purpose: to return what currPos currently points to(Find() should be called first, please)
	Pre: a BinaryTree exists
	Post: either an ItemType, or an exception
	*/

	bool Find(/*in*/ KeyType target);
	/*
	Purpose: to find a key within the BinaryTree object
	Pre: a BinaryTree exists
	Post: true if the key is found, false otherwise
	*/

	void Insert(/*in*/ T newItem);
	/*
	Purpose: to insert an element into the BinaryTree object
	Pre: a BinaryTree exists
	Post: a new element is inserted into the BinaryTree object
	*/

	void Delete();
	/*
	Purpose: to delete what currPos currently points to
	Pre: a BinaryTree exists
	Post: what currPos currently points to no longer exists
	*/

	void Clear();
	/*
	Purpose: to remove all elements within the BinaryTree object
	Pre: a BinaryTree exists
	Post: the BinaryTree object no longer contains any elements
	*/

	int ReturnLength() const;
	/*
	Purpose: to return the number of elements within the BinaryTree object
	Pre: a BinaryTree exists
	Post: the number of elements within the BinaryTree object is returned
	*/

	bool IsBalanced();
	/*
	Purpose: to return if the BinaryTree object is "balanced"(Due to how this implementation works, the BinaryTree object is always balanced).
	Pre: a BinaryTree exists
	Post: true is returned
	*/

	void operator= (const BinaryTree& orig);
	/*
	Purpose: to copy an existing BinaryTree object's data to another BinaryTree object
	Pre: 2 BinaryTree's exist
	Post: 2 BinaryTree objects contain the same data
	*/

	BinaryTree operator+ (const BinaryTree& rtOp) const;
	/*
	Purpose: to OR 2 BinaryTree object's data into 1 BinaryTree object
	Pre: 2 BinaryTree's exist
	Post: a new super BinaryTree object exists
	*/

	BinaryTree operator- (const BinaryTree& rtOp) const;
	/*
	Purpose: to !AND 2 BinaryTree object's data into 1 BinaryTree object
	Pre: 2 BinaryTree's exist
	Post: a new lesser BinaryTree object exists
	*/

	bool operator== (const BinaryTree& rtOp) const;
	/*
	Purpose: to compare 2 BinaryTre objects to each other
	Pre: 2 BinaryTree's exist
	Post: true if the BinaryTree objects data are the same, false otherwise
	*/

	bool operator!= (const BinaryTree& rtOp) const;
	/*
	Purpose: to compare 2 BinaryTre objects to each other
	Pre: 2 BinaryTree's exist
	Post: true if the BinaryTree objects data are not the same, false otherwise
	*/

	void PrintScreen(void (*func)(BinaryTree<T>));
	/*
	Purpose: to print the contents of the BinaryTree objects data
	Pre: a BinaryTree exists
	Post: an arbitrary function is called to handle printing
	*/

	void PrintFile(void (*func)(BinaryTree<T>));
	/*
	Purpose: to print the contents of the BinaryTree objects data
	Pre: a BinaryTree exists
	Post: an arbitrary function is called to handle printing
	*/

	void PrintReverse(void (*func)(BinaryTree<T>));
	/*
	Purpose: to print the contents of the BinaryTree objects data
	Pre: a BinaryTree exists
	Post: an arbitrary function is called to handle printing
	*/

	void PrintAsExists(void (*func)(BinaryTree<T>));
	/*
	Purpose: to print the contents of the BinaryTree objects data
	Pre: a BinaryTree exists
	Post: an arbitrary function is called to handle printing
	*/

protected:
	node<T> * Allocate();
	/*
	Purpose: to allocate more Heap space for use
	Pre: a BinaryTree exists
	Post: some chunk of memory is now ours
	*/

	void MakeTree(node<T> *arr, size_t arrCount);
	/*
	Purpose: to create a "complete" BinaryTree object(this is abused by Insert, Delete, operator+, and operator-)
	Pre: a BinaryTree exists, and Insert, Delete, operator+, or operator- was called
	Post: to create a "complete" BinaryTree object
	*/

	node<T> *root = nullptr;
	mutable node<T> *currPos = nullptr;
	mutable node<T> *prevPos = nullptr;

};

#include "BinaryTree.tpp"